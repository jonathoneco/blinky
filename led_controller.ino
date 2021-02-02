#define debug


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

    lights.loadPattern(currentPattern);
}


void loop() {
    UI.update();

    if (UI.getPattern() != currentPattern) {
        currentPattern = UI.getPattern();
        lights.loadPattern(currentPattern);
    }

    lights.update();

    UI.show();
    lights.show();

    delay(1);
}
