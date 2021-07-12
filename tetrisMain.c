#include "common.h"
#include "keyCurControl.h"
#include "blockStageControl.h"

#define START_CURPOS_R (0)
#define START_CURPOS_C (5 << 1)
#define SYS_DELAY 1

int main(void) {
    setlocale(LC_ALL, "");
    initscr();

    RemoveCursor();
    InitNewBlockPos(START_CURPOS_R, START_CURPOS_C);

    ChooseBlock();
    while (true) {
        BlockDown();
        sleep(SYS_DELAY);
    }

    endwin();
    return 0;
}
