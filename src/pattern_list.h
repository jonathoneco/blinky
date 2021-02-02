#pragma once

#include "common.h"
#include "pattern.h"

#define ADD_PATTERN(idx, Pattern, name) \
    patternFactories[idx] = (Factory *) new PatternFactory<Pattern>(); \
    UI.addPattern(name) \


#include "patterns/hsv.h"
#include "patterns/white_dot.h"
#include "patterns/stars.h"

#define NUM_PATTERNS 3


Factory *patternFactories[NUM_PATTERNS];

void patternInit() {
    ADD_PATTERN(0, PatternStars, "Stars");
    ADD_PATTERN(1, PatternWhiteDot, "White dot");
    ADD_PATTERN(2, PatternHSV, "HSV");
}
