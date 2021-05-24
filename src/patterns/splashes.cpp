#include "splashes.h"


void PatternSplashes::init() {
    FastLED.setBrightness(BRIGHTNESS_MAX);

    UI.addParam("SPEED", {1, 50, 1, false, 20});
    UI.addParam("SPAWN_RATE", {1, 20, 1, false, 7});
}


void PatternSplashes::update() {
    int speed = UI.getParam("SPEED");
    int spawn_rate = UI.getParam("SPAWN_RATE");

    for (int i = 0; i < NUM_LEDS; i++) {
        int r_sum = 0;
        int g_sum = 0;
        int b_sum = 0;
        for (int j = -radius; j <= radius; j++) {
            int led_idx = constrain(i + j, 0, NUM_LEDS - 1);
            r_sum += leds[FROM_LEFT(led_idx)].r;
            g_sum += leds[FROM_LEFT(led_idx)].g;
            b_sum += leds[FROM_LEFT(led_idx)].b;
        }

        int r_avg = r_sum / (2 * radius + 1);
        int g_avg = g_sum / (2 * radius + 1);
        int b_avg = b_sum / (2 * radius + 1);

        int current_mag = leds[FROM_LEFT(i)].r + leds[FROM_LEFT(i)].g + leds[FROM_LEFT(i)].b;
        int new_mag = r_avg + g_avg + b_avg;

        // Infection based on avg of neighbors
        if (new_mag >= current_mag) {
            if (random(brighten_prob) < speed) leds[FROM_LEFT(i)] = CRGB(r_avg, g_avg, b_avg);
        } else {
            if (random(darken_prob) < speed) leds[FROM_LEFT(i)] = CRGB(r_avg, g_avg, b_avg);
        }

        // Random infections starting
        if (random(100000) + current_mag * 4 < spawn_rate) leds[FROM_LEFT(i)] = CHSV(random(256), 255, 255);
    }
}
