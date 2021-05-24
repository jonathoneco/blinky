#include "trains.h"

#include "../common.h"


int signum(int input) {
    if (input > 0) return 1;
    if (input < 0) return -1;
    return 0;
}

int signum(float input) {
    if (input > 0) return 1;
    if (input < 0) return -1;
    return 0;
}


void PatternTrains::init() {
    FastLED.setBrightness(BRIGHTNESS_MAX);

    UI.addParam("TRAINS", {1, TOTAL_TRAINS, 1, false, 10});
    UI.addParam("SPEED", {1, 10, 1, false, 3});
    UI.addParam("TAIL_LENGTH", {5, 150, 5, false, 50});

    for (int i = 0; i < TOTAL_TRAINS; i++) {
        Train* train = trains + i;
        train->pos = random(0, NUM_LEDS);
        train->speed = random(1, 100) / 100.0;
        if (random(0, 2)) train->speed *= -1;
        train->tail = 0.5 + abs(train->speed);
        train->hue = random(0, 256); 
    }
}


void PatternTrains::update() {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
    }

    for (int i = 0; i < UI.getParam("TRAINS"); i++) {
        Train* train = trains + i;

        int speed = train->speed * UI.getParam("SPEED");
        if (speed == 0) speed = signum(train->speed);
        train->pos = (train->pos + speed + NUM_LEDS) % NUM_LEDS;

        leds[FROM_LEFT(train->pos)] = CHSV(train->hue, 255, 255);

        int tail_dir = -signum(train->speed);

        int tail_end = train->pos + train->tail * UI.getParam("TAIL_LENGTH") * tail_dir;

        for (int j = train->pos; j != tail_end; j += tail_dir) {
            CRGB newCol = CHSV(train->hue, 255, map(j, train->pos, tail_end, 255, 0));

            int led_idx = (j + NUM_LEDS) % NUM_LEDS;

            leds[FROM_LEFT(led_idx)].r += newCol.r;
            leds[FROM_LEFT(led_idx)].g += newCol.g;
            leds[FROM_LEFT(led_idx)].b += newCol.b;
        }
    }
}
