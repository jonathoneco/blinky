#include <FastLED.h>

#include "../config.h"
#include "ui/ui.h"

#define LED_LOOP(i) (i < NUM_LEDS_PER_STRIP) ? i : NUM_LEDS + NUM_LEDS_PER_STRIP - i - 1

extern CRGB leds[NUM_LEDS];

extern UserInterface UI;
