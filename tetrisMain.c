#include "common.h"
#include "keyCurControl.h"
#include "blockStageControl.h"

#define START_CURPOS_R (0)
#define START_CURPOS_C (5 << 1)

int main(void) {
    setlocale(LC_ALL, "");
    initscr();

    keypad(stdscr, true);
    nodelay(stdscr, true);
    RemoveCursor();
    InitKeyDelayRate(10);
    InitNewBlockPos(START_CURPOS_R, START_CURPOS_C);

    ChooseBlock();
    while (true) {
        BlockDown();
        ProcessKeyInput();
    }

    endwin();
    return 0;
}
