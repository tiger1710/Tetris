#include "common.h"
#include "point.h"
#include "blockInfo.h"
#include "keyCurControl.h"

static int currentBlockModel;
static int curPosR, curPosC;
static int rotateSte;

void InitNewBlockPos(const int r, const int c) {
    if (r < 0 || c < 0)
        return;

    curPosR = r; curPosC = c;

    SetCurrentCursorPos(r, c);
}

void ChooseBlock(void) {
    srand((unsigned int)time(NULL));
    currentBlockModel = (rand() % NUM_OF_BLOCK_MODEL) << 2;
}

int GetCurrentBlockIdx(void) {
    return currentBlockModel + rotateSte;
}

void ShowBlock(const char blockInfo[][4]) {
    point cursor = GetCurrentCursorPos();

    for (int row = 0; row < 4; row++)
        for (int col = 0; col < 4; col++) {
            SetCurrentCursorPos(cursor.r + row, cursor.c + (col << 1));
            if (blockInfo[row][col] == 1)
                printw("■");
        }
    SetCurrentCursorPos(cursor.r, cursor.c);

    refresh();
}

void DeleteBlock(const char blockInfo[][4]) {
    point cursor = GetCurrentCursorPos();

    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++) {
            SetCurrentCursorPos(cursor.r + r, cursor.c + (c << 1));
            if (blockInfo[r][c] == 1)
                printw("  ");
        }

    SetCurrentCursorPos(cursor.r, cursor.c);
}

void BlockDown(void) {
    DeleteBlock(blockModel[GetCurrentBlockIdx()]);
    curPosR++;

    SetCurrentCursorPos(curPosR, curPosC);
    ShowBlock(blockModel[GetCurrentBlockIdx()]);
}

void ShiftLeft(void) {
    DeleteBlock(blockModel[GetCurrentBlockIdx()]);
    curPosC -= 2;

    SetCurrentCursorPos(curPosR, curPosC);
    ShowBlock(blockModel[GetCurrentBlockIdx()]);
}

void ShiftRight(void) {
    DeleteBlock(blockModel[GetCurrentBlockIdx()]);
    curPosC += 2;

    SetCurrentCursorPos(curPosR, curPosC);
    ShowBlock(blockModel[GetCurrentBlockIdx()]);
}

void RotateBlock(void) {
    DeleteBlock(blockModel[GetCurrentBlockIdx()]);

    int nextRotSte = (rotateSte + 1) % 4;
    rotateSte = nextRotSte;

    SetCurrentCursorPos(curPosR, curPosC);
    ShowBlock(blockModel[GetCurrentBlockIdx()]);
}
