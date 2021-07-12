#ifndef __KEY_CUR_CONTROL_H_
#define __KEY_CUR_CONTROL_H_
#include "point.h"

void RemoveCursor(void);

point GetCurrentCursorPos(void);

void SetCurrentCursorPos(const int r, const int c);

#endif
