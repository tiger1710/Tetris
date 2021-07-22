#include "process.h"
#include "common.h"
#include "keyCurControl.h"
#include "blockStageControl.h"
#include "scoreLevelControl.h"

#define START_CURPOS_R (0)
#define START_CURPOS_C (10)

void Initialize(void) {
    srand((unsigned int)time(NULL));
    setlocale(LC_ALL, "");
    initscr();
    keypad(stdscr, true);
    nodelay(stdscr, true);

    InitKeyDelayRate(10);
    RemoveCursor();
    DrawGameBoard();
    ShowCurrentScoreAndLevel();
}

void StartGame(void) {
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
}

void Finalize(void) {
    SetCurrentCursorPos(10, 10);
    printw("GAME OVER ...");
    refresh();
    sleep(5);
    endwin();
}

