#pragma once

#include "../common.h"
#include "../pattern.h"

#define V_MAX 256
#define V_MIN 100

#define STEPS_MIN 500
#define STEPS_MAX 5000

class PatternDrift : public Pattern {
public:
    void init();
    void update();
private:
    float steps[NUM_LEDS];

    int old_hue;
    int new_hue;
    int old_val;
    int new_val;

    int step;

    void startOver();
};
