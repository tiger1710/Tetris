#include "keyCurControl.h"
#include <ncurses.h>

#define LEVEL_DIFF 2
#define LEVEL_UP_SCORE_DIFF 20

static int curGameLevel = 1;
static int curGameScore = 0;

void ShowCurrentScoreAndLevel(void) {
    SetCurrentCursorPos(4, 30);
    printw("§ 현재 레벨: %d §", curGameLevel);
    
    SetCurrentCursorPos(7, 30);
    printw("§ 현재 점수: %d §", curGameScore);
}

void GameLevelUp(void) {
    curGameLevel++;
    KeyDelaySpeedCtl(LEVEL_DIFF);
}

void AddGameScore(const int score) {
    if (score < 1)
        return;
    
    curGameScore += score;

    if (curGameLevel * LEVEL_UP_SCORE_DIFF <= curGameScore)
        GameLevelUp();
}
