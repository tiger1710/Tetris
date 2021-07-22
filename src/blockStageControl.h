#ifndef __BLOCKSTAGECONTROL_H_
#define __BLOCKSTAGECONTROL_H_

void InitNewBlockPos(const int r, const int c);
void ChooseBlock(void);
int GetCurrentBlockIdx(void);
void ShowBlock(const char blockInfo[4][4]);
void DeleteBlock(const char blockInfo[4][4]);
int BlockDown(void);

void ShiftLeft(void);
void ShiftRight(void);
void RotateBlock(void);

int DetectCollision(const int PosR, const int PosC, const char blockModel[4][4]);
void DrawGameBoard(void);
void AddCurrentBlockInfoToBoard(void);
int IsGameOver(void);

void DrawSolidBlocks(void);
void RemoveFillUpLine(void);
void SolidCurrentBlock(void);

#endif
