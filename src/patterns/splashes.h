#pragma once

#include "../common.h"
#include "../pattern.h"


class PatternSplashes : public Pattern {
public:
    void init();
    void update();
private:
    const int radius = 7;
    const int brighten_prob = 100;
    const int darken_prob = 150;
};
