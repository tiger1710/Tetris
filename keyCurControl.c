#include "common.h"
#include "point.h"

void RemoveCursor(void) {
    curs_set(0);
}

point GetCurrentCursorPos(void) {
    point cursor;
    getyx(stdscr, cursor.r, cursor.c);
    return cursor;
}


void SetCurrentCursorPos(const int r, const int c) {
    move(r, c);
}
