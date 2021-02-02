#pragma once

#include "../pattern.h"

#define TOTAL_TRAINS 20

typedef struct {
    int pos;
    float speed;
    float tail;
    int hue;
} Train;

class PatternTrains : public Pattern {
public:
    void init();
    void update();
private:
    Train trains[TOTAL_TRAINS];
};
