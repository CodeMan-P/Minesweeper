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
private:
	void refreshGameStatus();
	void resetEngine();
	bool lclick(Brick* brick);
	bool rclick(Brick* brick);
	bool midclick(Brick* brick);

	GameStatus gameStatus;
	
	Brick* bricks = NULL;
	void gameLoss();

	std::vector<Brick*> getNeighbourBrick(int x, int y);
	std::vector<Brick*> getNeighbourBrick(int x, int y, BrickStatus status);

	bool isNeighbourSafe(int x, int y);
	bool clickNeighbourBrick(int x, int y);

	

	int rows, cols, mineSum;
	int normalBrickSum;

	int brickSurpluses;
	
	int flagBrickSum;
};

