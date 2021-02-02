# Blinky

An addressable LED controller with an encoder/pushbutton and OLED display for user interaction.


## Interface

Main menu: use the encoder to scroll through the list of patterns, press the button to select a pattern.

Pattern view: use the encoder to scroll through the pattern's parameters, press the button to edit the parameter. Press the button again to stop editing.


## Hardware and Backend

Blinky runs on a Teensy 4.0, controlling two 300-LED strips in parallel with FastLED.
This can be easily upgraded to 4 LED strips with no additional hardware, or 8 strips by adding a second level converter.

Encoder input is debounced in hardware using a simple RC filter on each line.
Pushbutton input is debounced in software with the `Bounce` library.

Parts:

- [LED strips](https://amzn.com/B07BH37JGC)
- [Teensy 4.0](https://www.pjrc.com/store/teensy40.html)
- [Level converter](https://amzn.com/B07LG646VS)
- [OLED display](https://amzn.com/B00O2LLT30)
- [Encoder w/ pushbutton](https://amzn.com/B07DM2YMT4)
- [Power supply](https://amzn.com/B07TSKK4FR)
- A couple resistors and capacitors for debouncing the encoder

Teensy pinout:
- 5V, GND from power supply
- 3V output to level converter low voltage
- Pins 19, 18, 14, 15 connected to level converter LV1, LV2, LV3, LV4 respectively, for LED strips
- Pins 24, 25 used for I2C communication to OLED
- Pins 8, 9 used for encoder
- Pin 7 used for pushbutton

This leaves pins 17, 16, 22, 23, 20, 21 as potential additional LED strip outputs (see [FastLED docs](https://github.com/FastLED/FastLED/wiki/Parallel-Output#parallel-output-on-the-teensy-4)),
and any of the aforementioned, as well as 26 and 27, available for analog input for audio processing in the future.


## Writing Patterns

Patterns should extend the `Pattern` class defined in `src/pattern.h` and implement `init()` and `update()` functions.
`init()` is run once each time the pattern is loaded, after which `update()` is called repeatedly, hopefully about once every 10ms.

`update()` should run quickly, so as not to interfere with other processes, so DO NOT call `delay()` internally and in general do not write anything meant to display more than one "frame" of animation at a time.

All patterns (and header files) should be in `src/patterns/`.

### Writing Pixels

You can set LEDs by setting elements of the global `leds[]` array to `CRGB` or `CHSV` values (see [FastLED](https://github.com/FastLED/FastLED/wiki/Pixel-reference)).
A helpful macro `LED_LOOP(i)` is provided to remap the indexes of the two strips into a closed loop.
All the LEDs will be blanked (set to black) before the pattern is loaded.

### Pattern Parameters

Patterns can have an unlimited number of parameters, which can be adjusted in real time through the user interface.

To use parameters, put `UI.addParam("PARAM_NAME", {MIN_VAL, MAX_VAL, STEP_SIZE, LOOP, DEFAULT_VAL});"` in your pattern's `init()`.

`"PARAM_NAME"` is a string, `MIN_VAL`, `MAX_VAL`, `STEP_SIZE`, and `DEFAULT_VAL` are `int`s, and `LOOP` is a `bool`.
`STEP_SIZE` gives the change in value from one tick of the encoder. 
If `LOOP` is true, the value will loop from maximum to minimum and vice versa. If false it will be capped at maximum and minimum.

To get the value, call `UI.getParam("PARAM_NAME")`, which returns `int`.

### Pattern List

After writing a pattern, it must be added in `src/pattern_list.h` to be recognized by the system.

Insert the pattern by `#include`-ing the header file, adding an `ADD_PATTERN(idx, PatternClass, "Pattern Name");` call in `patternInit()`, and adjusting `NUM_PATTERNS`.

`idx` should be in strict ascending order from 0 up to `NUM_PATTERNS - 1`.
`"Pattern Name"` should be kept short to fit on a single line on the OLED display.
