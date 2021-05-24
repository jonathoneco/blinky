#pragma once

#include "common.h"
#include "pattern.h"

#define ADD_PATTERN(idx, Pattern, name) \
    patternFactories[idx] = (Factory *) new PatternFactory<Pattern>(); \
    UI.addPattern(name) \


#include "patterns/hsv.h"
#include "patterns/white_dot.h"
#include "patterns/stars.h"
#include "patterns/trains.h"
#include "patterns/drift.h"
#include "patterns/flicker.h"
#include "patterns/alarm.h"
#include "patterns/splashes.h"

#define NUM_PATTERNS 7


Factory *patternFactories[NUM_PATTERNS];

void patternInit() {
    ADD_PATTERN(0, PatternDrift, "Drift");
    ADD_PATTERN(1, PatternSplashes, "Splashes");
    ADD_PATTERN(2, PatternTrains, "Trains");
    ADD_PATTERN(3, PatternStars, "Stars");
    ADD_PATTERN(4, PatternAlarm, "Alarm");
    ADD_PATTERN(5, PatternHSV, "HSV");
    ADD_PATTERN(6, PatternWhiteDot, "White dot");
}
