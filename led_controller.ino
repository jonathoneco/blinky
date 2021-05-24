#define debug

#include <TimeLib.h>

#include "src/common.h"

#include "src/lights.h"
#include "src/ui/ui.h"


CRGB leds[NUM_LEDS];

UserInterface UI;
LightsControl lights;

unsigned short currentPattern = 0;


void setup() {
#ifdef debug
    Serial.begin(9600);
#endif
    setSyncProvider(Teensy3Clock.get);

    randomSeed(analogRead(13));

    lights.loadPattern(currentPattern);

    UI.show();
}


void loop() {
    UI.update();

    if (UI.getPattern() != currentPattern) {
        currentPattern = UI.getPattern();
        lights.loadPattern(currentPattern);
    }

    lights.update();
    lights.show();

    delay(1);
}
