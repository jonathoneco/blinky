#include "display.h"

#include <Fonts/FreeSansBold9pt7b.h>


Display::Display() {
    oled = Adafruit_SSD1306(DISP_WIDTH, DISP_HEIGHT, &Wire2);

    if (!oled.begin(SSD1306_SWITCHCAPVCC, DISP_ADDRESS)) {
#ifdef debug
        Serial.println(F("Display allocation failed"));
#endif
    }

    oled.clearDisplay();
    oled.setTextColor(SSD1306_WHITE);

    oled.display();
}


void Display::show() {
    if (disp_on) {
        oled.display();
    }
}

void Display::turn_off() {
    if (disp_on) {
        oled.clearDisplay();
        oled.display();
        disp_on = false;
    }
}

void Display::turn_on() {
    disp_on = true;
}


void Display::blank() {
    oled.clearDisplay();
}


void Display::putHeader(String text) {
    oled.setFont(&FreeSansBold9pt7b);
    oled.setTextColor(SSD1306_WHITE);
    oled.setCursor(0, 12);

    oled.println(text.c_str());
}


void Display::putText(String text, int line, bool hl) {
    oled.setFont(); // return to standard font

    if (hl) {
        oled.fillRect(0, HEADER_HEIGHT + line * LINE_HEIGHT,
                      DISP_WIDTH, LINE_HEIGHT, SSD1306_WHITE);
        oled.setTextColor(SSD1306_BLACK);
    } else {
        oled.fillRect(0, HEADER_HEIGHT + line * LINE_HEIGHT,
                      DISP_WIDTH, LINE_HEIGHT, SSD1306_BLACK);
        oled.setTextColor(SSD1306_WHITE);
    }

    oled.setCursor(LINE_PAD_LEFT, HEADER_HEIGHT + line * LINE_HEIGHT + LINE_PAD_TOP);
    oled.println(text.c_str());
}
