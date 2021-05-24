#include "hardware.h"


Hardware::Hardware() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    enc = new Encoder(ENCODER_PIN_A, ENCODER_PIN_B);
    bouncer = new Bounce(BUTTON_PIN, BUTTON_DELAY);
}


bool Hardware::update() {
    bool btn_change = bouncer->update();

    enc_prev = enc_pos;
    enc_pos = enc->read() / 4;

    return (btn_change || (enc_pos != enc_prev));
}


void Hardware::set_enc(long pos) {
    enc->write(pos);
}

long Hardware::read_enc() {
    return enc_pos;
}

bool Hardware::encIncrease() {
    return (enc_pos > enc_prev);
}

bool Hardware::encDecrease() {
    return (enc_pos < enc_prev);
}


bool Hardware::buttonPress() {
    return bouncer->fallingEdge();
}
