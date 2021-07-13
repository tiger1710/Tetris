#include "common.h"
#include "keyCurControl.h"
#include "blockStageControl.h"

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

int kbhit(void) {
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    }

    return 0;
}

void ProcessKeyInput(void) {
    for (int i = 0; i < KEY_SENSITIVE; i++) {
        int key = getch();
        switch (key) {
        case KEY_LEFT:
            ShiftLeft();
            break;
        case KEY_RIGHT:
            ShiftRight();
            break;
        case KEY_UP:
            RotateBlock();
            break;
        default:
            break;
        }
        if (i % keyDelayRate == 0)
            usleep(SYS_DELAY);
    }
}

void InitKeyDelayRate(int rate) {
    if (rate < 1)
        return;
    keyDelayRate = rate;
}
