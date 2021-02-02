#pragma once

#include <map>

#include "display.h"


struct PatternParam {
    int min_val;
    int max_val;
    int step;
    bool loop;
    int val;
};


int restrictVal(int val, int min_val, int max_val, bool loop);


class PatternView {
public:
    void show(Display *disp);

    void setTitle(String t);

    void addParam(String name, PatternParam param);
    int getParam(String name);

    void resetScroll();

    void encoderInc();
    void encoderDec();
    void buttonPress();

    bool shouldExit();
private:
    String title;
    std::map<String, PatternParam> params;

    std::map<String, PatternParam>::iterator current_param;

    bool focused = false;
    bool toExit = false;
};
