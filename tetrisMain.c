#include "blockStageControl.h"
#include "keyCurControl.h"
#include "scoreLevelControl.h"
#include <ncurses.h>
#include <unistd.h>
#include <locale.h>

#define START_CURPOS_R (0)
#define START_CURPOS_C (10)

int main(void) {
    setlocale(LC_ALL, "");
    initscr();
    keypad(stdscr, true);
    nodelay(stdscr, true);

    InitKeyDelayRate(10);
    RemoveCursor();
    DrawGameBoard();
    ShowCurrentScoreAndLevel();

    while (true) {
        InitNewBlockPos(START_CURPOS_R + 2, START_CURPOS_C);
        ChooseBlock();
        if (IsGameOver())
            break;

        while (true) {
            if (!BlockDown()) {
                break;
            }
            if (ProcessKeyInput()) {
                break;
            }
        }
    }
    SetCurrentCursorPos(10, 10);
    printw("GAME OVER ...");
    refresh();
    sleep(3);
    

    endwin();
    return 0;
}
