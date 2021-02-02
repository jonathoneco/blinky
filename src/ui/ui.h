#pragma once

#include <vector>
#include <unordered_map>

#include "hardware.h"
#include "display.h"
#include "scrollview.h"
#include "patternview.h"


class UserInterface {
public:
    UserInterface();

    void show();
    void update();

    void showMainMenu();
    void showPatternView(unsigned short idx);

    void addPattern(String name);
    bool wantsNewPattern();
    unsigned short getPattern();

    void addParam(String name, PatternParam param);
    int getParam(String name);
private:
    Hardware hw;
    Display disp;

    ScrollView mainMenu;
    std::vector<PatternView> patternViews;

    bool onMainMenu;

    unsigned short currentPattern;
    bool patternUpdate;
};
