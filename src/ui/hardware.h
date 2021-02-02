#include <Encoder.h>
#include <Bounce.h>

#include "../../config.h"


class Hardware {
public:
    Hardware();

    void update();

    void set_enc(long pos);
    long read_enc();
    bool encIncrease();
    bool encDecrease();

    bool buttonPress();
private:
    Encoder *enc;
    Bounce *bouncer;

    long enc_pos = 0;
    long enc_prev = 0;
};
