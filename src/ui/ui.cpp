#include "ui.h"

UserInterface::UserInterface() {
    mainMenu.setTitle("PATTERNS");

    currentPattern = 0;
    onMainMenu = true;

    last_active = millis();
}


void UserInterface::show() {
    if (onMainMenu) {
        mainMenu.show(&disp);
    } else {
        patternViews.at(currentPattern).show(&disp);
    }
}


void UserInterface::update() {
    if (hw.update()) {
        disp.turn_on();
        last_active = millis(); // reset display blanking timer

        if (onMainMenu) {
            if (hw.encIncrease()) mainMenu.scrollForward();
            if (hw.encDecrease()) mainMenu.scrollBack();

            if (hw.buttonPress()) {
                currentPattern = mainMenu.getSelected();
                patternViews.at(currentPattern).resetScroll();
                onMainMenu = false;
            }
        } else {
            if (hw.encIncrease()) patternViews.at(currentPattern).encoderInc();
            if (hw.encDecrease()) patternViews.at(currentPattern).encoderDec();
            if (hw.buttonPress()) patternViews.at(currentPattern).buttonPress();

            if (patternViews.at(currentPattern).shouldExit()) {
                onMainMenu = true;
            }
        }

        show();
    }

    if ((millis() - last_active) >= SLEEP_TIME) { // display blanking on inactivity
        disp.turn_off();
    }
}


void UserInterface::addPattern(String name) {
    mainMenu.addEntry(name);

    PatternView pv;
    pv.setTitle(name);
    patternViews.push_back(pv);
}

unsigned short UserInterface::getPattern() {
    return currentPattern;
}


void UserInterface::addParam(String name, PatternParam param) {
    patternViews.at(currentPattern).addParam(name, param);
}

int UserInterface::getParam(String name) {
    return patternViews.at(currentPattern).getParam(name);
}
