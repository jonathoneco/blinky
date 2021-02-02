#include "patternview.h"


void PatternView::show(Display *disp) {
    disp->blank();

    // First entry is back button
    disp->putText("BACK", 0, current_param == params.end());

    unsigned short line = 1;
    for (auto param = params.begin(); param != params.end(); param++) {
        String text;
        if (focused && (param == current_param)) {
            text = "> " + param->first + ": " + String(param->second.val);
        } else {
            text = "  " + param->first + ": " + String(param->second.val);
        }
        disp->putText(text, line, (param == current_param));
        line++;
    }

    disp->putHeader(title);

    disp->show();
}


void PatternView::setTitle(String t) {
    title = t;
}


void PatternView::resetScroll() {
    current_param = params.end();
}


void PatternView::addParam(String name, PatternParam param) {
    // Add the parameter only if it is not in the map.
    // This allows addParam to be called multiple times without resetting the
    // parameter each time.
    if (params.find(name) == params.end()) params[name] = param;
}

int PatternView::getParam(String name) {
    // Check that the param exists
    if (params.find(name) == params.end()) {
#ifdef debug
        Serial.println("Parameter " + name + " does not exist.");
#endif
        return 0.;
    }

    return params.at(name).val;
}


void PatternView::encoderInc() {
    if (focused) {
        PatternParam *param = &(current_param->second);
        param->val = restrictVal(param->val + param->step, param->min_val, param->max_val, param->loop);
    } else {
        // Handle scrolling through params + back button
        if (current_param == params.end()) {
            // If on back button, go to first param
            current_param = params.begin();
        } else {
            // If on a param, go to next param and loop
            current_param++;
        }
    }
}

void PatternView::encoderDec() {
    if (focused) {
        PatternParam *param = &(current_param->second);
        param->val = restrictVal(param->val - param->step, param->min_val, param->max_val, param->loop);
    } else {
        // Handle scrolling through params + back button
        // If on a param, go to previous param or back button
        if (current_param == params.begin()) current_param = params.end();
        else current_param--;
    }
}

void PatternView::buttonPress() {
    if (current_param == params.end()) {
        toExit = true;
    } else {
        focused = !focused;
    }
}


bool PatternView::shouldExit() {
    if (toExit) {
        toExit = false;
        return true;
    }
    return false;
}


int restrictVal(int val, int min_val, int max_val, bool loop) {
    if (val > max_val) {
        if (loop) val = min_val + (val - max_val);
        else val = max_val;
    }

    if (val < min_val) {
        if (loop) val = max_val + (val - min_val);
        else val = min_val;
    }

    return val;
}
