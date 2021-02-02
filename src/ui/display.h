#pragma once

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define DISP_WIDTH 128
#define DISP_HEIGHT 64

#define DISP_ADDRESS 0x3C

#define LINE_HEIGHT 10
#define HEADER_HEIGHT 16
#define LINE_PAD_TOP 1
#define LINE_PAD_LEFT 2

#define MAX_LINE 5


class Display {
public:
    Display();
    void show();

    void blank();
    void putHeader(String text);
    void putText(String text, int line, bool hl);
private:
    Adafruit_SSD1306 oled;
};
