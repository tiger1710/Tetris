#include "common.h"
#include "blockInfo.h"
#include "keyCurControl.h"
#include "blockStageControl.h"
#include "scoreLevelControl.h"
#include <ncurses.h>

#define GBOARD_WIDTH 10
#define GBOARD_HEIGHT 20

#define GBOARD_ORIGIN_R 2
#define GBOARD_ORIGIN_C 4

static char gameBoardInfo[GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2] = { 0, };

static int currentBlockModel;
static int curPosR, curPosC;
static int rotateSte;

void InitNewBlockPos(const int r, const int c) {
    if (r < 0 || c < 0)
        return;

    curPosR = r;
    curPosC = c;

    SetCurrentCursorPos(r, c);
}

void ChooseBlock(void) {
    currentBlockModel = (rand() % NUM_OF_BLOCK_MODEL) << 2;
}

int GetCurrentBlockIdx(void) {
    return currentBlockModel + rotateSte;
}

void ShowBlock(const char blockInfo[4][4]) {
    point curPos = GetCurrentCursorPos();

    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            SetCurrentCursorPos(curPos.r + r, curPos.c + (c << 1));
            if (blockInfo[r][c])
                printw("■");
        }
    }
    refresh();

    SetCurrentCursorPos(curPos.r, curPos.c);
}

void DeleteBlock(const char blockInfo[4][4]) {
    point curPos = GetCurrentCursorPos();

    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            SetCurrentCursorPos(curPos.r + r, curPos.c + (c << 1));
            if (blockInfo[r][c])
                printw("  ");
        }
    }
    refresh();

    SetCurrentCursorPos(curPos.r, curPos.c);
}

int BlockDown(void) {
    if (!DetectCollision(curPosR + 1, curPosC, blockModel[GetCurrentBlockIdx()])) {
        AddCurrentBlockInfoToBoard();
        RemoveFillUpLine();
        return 0;
    }

    DeleteBlock(blockModel[GetCurrentBlockIdx()]);
    curPosR++;

    SetCurrentCursorPos(curPosR, curPosC);
    ShowBlock(blockModel[GetCurrentBlockIdx()]);

    return 1;
}

void ShiftLeft(void) {
    if (!DetectCollision(curPosR, curPosC - 2, blockModel[GetCurrentBlockIdx()]))
        return;

    DeleteBlock(blockModel[GetCurrentBlockIdx()]);
    curPosC -= 2;

    SetCurrentCursorPos(curPosR, curPosC);
    ShowBlock(blockModel[GetCurrentBlockIdx()]);
}

void ShiftRight(void) {
    if (!DetectCollision(curPosR, curPosC + 2, blockModel[GetCurrentBlockIdx()]))
        return;

    DeleteBlock(blockModel[GetCurrentBlockIdx()]);
    curPosC += 2;

    SetCurrentCursorPos(curPosR, curPosC);
    ShowBlock(blockModel[GetCurrentBlockIdx()]);
}

void RotateBlock(void) {
    DeleteBlock(blockModel[GetCurrentBlockIdx()]);

    int beforeRotSte = rotateSte;
    int nextRotSte = (rotateSte + 1) % 4;
    rotateSte = nextRotSte;

    if (!DetectCollision(curPosR, curPosC, blockModel[GetCurrentBlockIdx()])) {
        rotateSte = beforeRotSte;
        return;
    }

    SetCurrentCursorPos(curPosR, curPosC);
    ShowBlock(blockModel[GetCurrentBlockIdx()]);
}

int DetectCollision(const int posR, const int posC, const char blockModel[4][4]) {
    int arrR = posR - GBOARD_ORIGIN_R;
    int arrC = (posC - GBOARD_ORIGIN_C) >> 1;

    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (blockModel[r][c] && gameBoardInfo[arrR + r][arrC + c])
                return 0;
        }
    }

    return 1;
}

void DrawGameBoard(void) {
    for (int r = 0; r <= GBOARD_HEIGHT; r++) {
        SetCurrentCursorPos(GBOARD_ORIGIN_R + r, GBOARD_ORIGIN_C);

        if (r == GBOARD_HEIGHT) {
            printw("┗");
        } else {
            printw("┃");
        }

    }
    for (int r = 0; r <= GBOARD_HEIGHT; r++) {
        SetCurrentCursorPos(GBOARD_ORIGIN_R + r, GBOARD_ORIGIN_C + ((GBOARD_WIDTH + 1) << 1));

        if (r == GBOARD_HEIGHT) {
            printw("┛");
        } else {
            printw("┃");
        }
    }
    for (int c = 1; c < GBOARD_WIDTH + 1; c++) {
        SetCurrentCursorPos(GBOARD_ORIGIN_R + GBOARD_HEIGHT, GBOARD_ORIGIN_C + (c << 1));
        printw("━");
    }
    refresh();

    SetCurrentCursorPos(0, 0);

    for (int r = 0; r < GBOARD_HEIGHT; r++) {
        gameBoardInfo[r][0] = 1;
        gameBoardInfo[r][GBOARD_WIDTH + 1] = 1;
    }
    for (int c = 0; c < GBOARD_WIDTH + 2; c++) {
        gameBoardInfo[GBOARD_HEIGHT][c] = 1;
    }
}

void AddCurrentBlockInfoToBoard(void) {
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            int arrCurR = curPosR - GBOARD_ORIGIN_R;
            int arrCurC = (curPosC - GBOARD_ORIGIN_C) >> 1;

            if (blockModel[GetCurrentBlockIdx()][r][c]) {
                gameBoardInfo[arrCurR + r][arrCurC + c] = 1;
            }
        }
    }
}

int IsGameOver(void) {
    if (!DetectCollision(curPosR, curPosC, blockModel[GetCurrentBlockIdx()]))
        return 1;

    return 0;
}

void DrawSolidBlocks(void) {
    for (int r = 0; r < GBOARD_HEIGHT; r++) {
        for (int c = 1; c < GBOARD_WIDTH + 1; c++) {
            int cursR = r + GBOARD_ORIGIN_R;
            int cursC = (c << 1) + GBOARD_ORIGIN_C;
            SetCurrentCursorPos(cursR, cursC);

            if (gameBoardInfo[r][c]) {
                printw("■");
            } else {
                printw("  ");
            }
        }
    }
    refresh();
}

void RemoveFillUpLine(void) {
    for (int r = GBOARD_HEIGHT - 1, c; r > 0; r--) {
        for (c = 1; c < GBOARD_WIDTH + 1; c++) {
            if (gameBoardInfo[r][c] != 1)
                break;
        }
        if (c == (GBOARD_WIDTH + 1)) {
            for (int line = 0; r - line > 0; line++) {
                memcpy(
                    (gameBoardInfo[r - line] + 1),
                    (gameBoardInfo[r - line - 1] + 1),
                    GBOARD_WIDTH * sizeof(char)
                );
            }

            r++;
            AddGameScore(10);
            ShowCurrentScoreAndLevel();
        }
    }

    DrawSolidBlocks();
}

void SolidCurrentBlock(void) {
    while (BlockDown())
        ;
}
