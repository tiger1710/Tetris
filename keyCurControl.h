#ifndef __KEY_CUR_CONTROL_H_
#define __KEY_CUR_CONTROL_H_
#include "point.h"

#define KEY_SENSITIVE 100
#define SYS_DELAY 20000 //sleep(1) == Sleep(1000) == usleep(1,000,000)

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

static int keyDelayRate;

void RemoveCursor(void);

point GetCurrentCursorPos(void);

void SetCurrentCursorPos(const int r, const int c);

void ProcessKeyInput(void);

void InitKeyDelayRate(int rate);

#endif
