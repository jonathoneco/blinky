#pragma once

#include "../pattern.h"


#define N_BINS 100
#define LEDS_PER_BIN 1
#define HUE_CHANGE 40 // change from middle to edge
#define HUE_RATE 30 // rate at which hue shifts at middle

class PatternMusicViz : public Pattern {
public:
    void init();
    void update();
private:
    char bins[N_BINS];
    bool synced = false;
    int pos = 0;
    int base_hue;
    int cnt = 0;
};
