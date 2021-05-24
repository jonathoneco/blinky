#include <FastLED.h>

#include "../config.h"
#include "ui/ui.h"

#define LED_LOOP(i) (i < NUM_LEDS_PER_STRIP) ? i : NUM_LEDS + NUM_LEDS_PER_STRIP - i - 1
#define FROM_LEFT(i) ( ((i < NUM_LEDS_PER_STRIP) ? NUM_LEDS_PER_STRIP - 1 - i : i) )
#define FROM_RIGHT(i) ( ((i < NUM_LEDS_PER_STRIP) ? NUM_LEDS - 1 - i : i - NUM_LEDS_PER_STRIP) )

extern CRGB leds[NUM_LEDS];

extern UserInterface UI;
