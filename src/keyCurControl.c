#include "keyCurControl.h"
#include "common.h"
#include "point.h"
#include "blockStageControl.h"

#define KEY_SENSITIVE 100
#define SYS_DELAY 20000

static int keyDelayRate;

void RemoveCursor(void) {
    curs_set(0);
}

point GetCurrentCursorPos(void) {
    point curPoint;
    getyx(stdscr, curPoint.r, curPoint.c);
    return curPoint;
}

void SetCurrentCursorPos(const int r, const int c) {
    move(r, c);
}

int ProcessKeyInput(void) {
    const char KEY_SPACE = ' ';
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
        case KEY_SPACE:
            SolidCurrentBlock();
            return 1;
        default:
            break;
        }
        if (i % keyDelayRate == 0)
            usleep(SYS_DELAY);
    }

    return 0;
}

void InitKeyDelayRate(const int rate) {
    if (rate < 1)
        return;

    keyDelayRate = rate;
}

void KeyDelaySpeedCtl(const int addSpeed) {
    keyDelayRate += addSpeed;
}
