#pragma once

#include <vector>

#include "display.h"


class ScrollView {
public:
    void show(Display *disp);

    void setTitle(String t);

    void addEntry(String name);

    void scrollForward();
    void scrollBack();

    unsigned short getSelected();
private:
    String title;
    std::vector<String> entries;
    unsigned short scroll_pos = 0;
};
