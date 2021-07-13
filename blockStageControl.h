#ifndef __BLOCK_STAGE_CONTROL_H_
#define __BLOCK_STAGE_CONTROL_H_

void InitNewBlockPos(const int r, const int c);

void ChooseBlock(void);

int GetCurrentBlockIdx(void);

void ShowBlock(const char blockInfo[][4]);

void DeleteBlock(const char blockInfo[][4]);

void BlockDown(void);

void ShiftLeft(void);

void ShiftRight(void);

void RotateBlock(void);

#endif
