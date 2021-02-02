#include "pattern.h"

class LightsControl {
public:
    LightsControl();
    void loadPattern(unsigned short idx);
    void update();
    void show();
private:
    Pattern *pattern;
};
