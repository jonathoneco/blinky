#pragma once

#include "../common.h"
#include "../pattern.h"

#define SHIFT_RATE 1
#define SHIFT_CNT 10

class PatternHSV : public Pattern {
public:
    void init();
    void update();
private:
    CHSV color;
    int cnt;
};
