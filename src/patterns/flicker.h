#pragma once

#include "../common.h"
#include "../pattern.h"

#define LEN_LIGHT 30
#define LEN_GAP 12
#define LIGHTS_PER_SIDE (NUM_LEDS_PER_STRIP / (LEN_LIGHT + LEN_GAP))


class PatternFlicker : public Pattern {
public:
    void init();
    void update();
private:
    int countdowns_left[LIGHTS_PER_SIDE]; // countdown to begin flicker
    int countdowns_right[LIGHTS_PER_SIDE];
    int durations_left[LIGHTS_PER_SIDE]; // duration of flicker
    int durations_right[LIGHTS_PER_SIDE];
};
