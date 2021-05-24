#include "alarm.h"

#include <TimeLib.h>

#include "../common.h"


void PatternAlarm::init() {
    FastLED.setBrightness(BRIGHTNESS_MAX);

    UI.addParam("WAKE_HOUR", {0, 23, 1, true, 8});
    UI.addParam("WAKE_MINUTE", {0, 59, 1, true, 30});
    UI.addParam("SLEEP_HOUR", {0, 23, 1, true, 23});
    UI.addParam("SLEEP_MINUTE", {0, 59, 1, true, 30});
}

void PatternAlarm::update() {
    int morning_end = UI.getParam("WAKE_HOUR") * 60 + UI.getParam("WAKE_MINUTE");
    int morning_start = morning_end - 30;

    int evening_end = UI.getParam("SLEEP_HOUR") * 60 + UI.getParam("SLEEP_MINUTE");
    int evening_start = evening_end - 30;

    int curr_time = hour() * 60 + minute();

    int sat, val;
     if (curr_time > morning_end && curr_time < evening_start) { // day
        sat = 0;
        val = 255;
    } else if (curr_time >= evening_start && curr_time <= evening_end) { // evening
        sat = map(curr_time, evening_start, evening_end, 0, 255);
        val = map(curr_time, evening_start, evening_end, 255, 0);
    } else if (curr_time >= morning_start && curr_time <= morning_end) { // morning
        sat = map(curr_time, morning_start, morning_end, 255, 0);
        val = map(curr_time, morning_start, morning_end, 0, 255);
    } else { // night
        sat = 255;
        val = 0;
    }

    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(30, sat, val);
    }
}
