#pragma once

#include "../pattern.h"

#define SPECIAL_FREQUENCY 100000 // chance of event is 1 / SPECIAL_FREQUENCY


class PatternStars : public Pattern {
public:
    void init();
    void update();
};
