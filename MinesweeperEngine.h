#pragma once
#include "windows.h"
#include<vector>

enum BrickStatus
{
	EMPTY,//空
	NORMAL,//正常
	SUSPICIOUS,//?
	FLAG,//旗帜
	NUMBER,//数字
	MINE//地雷
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
public:
	int x = 0;
	int y = 0;
	bool isMine = false;
	int mineNumber = 0;
	BrickStatus brickStatus = NORMAL;
};
class MinesweeperEngine
{
public:
	MinesweeperEngine();
	~MinesweeperEngine();
	bool initBricks(int rows, int cols, int mineSum);
	bool clickBrick(int x, int y, BrickClickEnum ctype);
	GameStatus getGameStatus();
	BrickStatus getBrickStatus(int x, int y);
	Brick getBrick(int x, int y);
	int getNeighbourMineCount(int x, int y);
private:
	GameStatus gameStatus;
	void resetEngine();
	Brick* bricks = NULL;
	void gameLoss();

	std::vector<Brick*> getNeighbourBrick(int x, int y);
	std::vector<Brick*> getNeighbourBrick(int x, int y, BrickStatus status);

	bool isNeighbourFlagEqualNumber(int x, int y);
	void clickNeighbourBrick(int x, int y);

	

	int rows, cols, mineSum;
	int normalBrickSum;
	int flagBrickSum;
};

