#pragma once
#include "windows.h"
#include<vector>
//(0,0)-----------------------x
// |
// |
// |    (x,y) <==> (col,row)
// |
// |
// |
// |
// y
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
	MIDDLE,// DBL DBR LR,
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
	

	int getBrickSurpluses();
	int getMineNumber();
	void stop();
private:
	void refreshGameStatus();
	void resetEngine();
	bool lclick(Brick* brick);
	bool rclick(Brick* brick);
	bool midclick(Brick* brick);

	GameStatus gameStatus;
	
	Brick* bricks = NULL;
	void gameLoss();

	std::vector<Brick*> getNeighbourBrick(Brick* brick);
	std::vector<Brick*> getNeighbourBrick(Brick* brick, BrickStatus status);

	bool isNeighbourSafe(Brick* brick);
	bool clickNeighbourBrick(Brick* brick);

	void lclickNormal(Brick* brick);
	int getNeighbourMineCount(Brick* brick);
	int rows, cols, mineSum;
	int normalBrickSum;

	int brickSurpluses;
	
	int flagBrickSum;
};

