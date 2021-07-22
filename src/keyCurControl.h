#ifndef __KEYCURCONTROL_H_
#define __KEYCURCONTROL_H_
#include "point.h"

void RemoveCursor(void);
point GetCurrentCursorPos(void);
void SetCurrentCursorPos(const int r, const int c);

int ProcessKeyInput(void);
void InitKeyDelayRate(const int rate);

void KeyDelaySpeedCtl(const int addSpeed);

#endif
