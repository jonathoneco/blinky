#pragma once

#include "../pattern.h"

#define SPEED 1

class PatternWhiteDot : public Pattern {
public:
    void init();
    void update();
private:
    int pos;
};
