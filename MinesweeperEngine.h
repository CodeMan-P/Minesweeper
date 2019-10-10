#pragma once
#include "windows.h"


enum BrickStatus
{
	EMPTY,//��
	NORMAL,//����
	SUSPICIOUS,//?
	FLAG,//����
	NUMBER,//����
	MINE//����
};
enum GameStatus {
	UNDERWAY,
	WIN,
	LOSS,
};
enum BrickClickEnum
{
	L,
	R,
	LR,
	MIDDLE,
};
class Brick {
private:
	int x, y;
	bool isMine = false;
	int mineNumber = 0;
	BrickStatus status;
};
class MinesweeperEngine
{
public:
	MinesweeperEngine();
	~MinesweeperEngine();
	void initBricks(int rows, int cols,int mineSum);
	void clickBrick(int x,int y, BrickClickEnum ctype);
	GameStatus getGameStatus();
	BrickStatus getBrickStatus();
private:
	void resetEngine();
	Brick* bricks = NULL;
	void gameLoss();
	void clickNeighbourBrick(int x, int y);
	int getNeighbourMineCount(int x, int y);
	int rows, cols, mineSum;
	int normalBrickSum;
	int flagBrickSum;
};

