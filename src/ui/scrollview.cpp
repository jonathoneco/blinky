#include "scrollview.h"


void ScrollView::show(Display *disp) {
    disp->blank();

    // If we've scrolled far, start the view with an offset so everything fits
    unsigned short startline = max(0, scroll_pos - MAX_LINE + 2);
    for (unsigned short line = startline; line < entries.size(); line++) {
        disp->putText(entries.at(line), line - startline, (line == scroll_pos));
    }

    disp->putHeader(title);

    disp->show();
}


void ScrollView::setTitle(String t) {
    title = t;
}

void ScrollView::addEntry(String name) {
    entries.push_back(name);
}


void ScrollView::scrollForward() {
    if (scroll_pos == entries.size() - 1) {
        scroll_pos = 0;
    } else {
        scroll_pos++;
    }
}

void ScrollView::scrollBack() {
    if (scroll_pos == 0) {
        scroll_pos = entries.size() - 1;
    } else {
        scroll_pos--;
    }
}


unsigned short ScrollView::getSelected() {
    return scroll_pos;
}
