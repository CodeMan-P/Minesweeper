#include "MinesweeperEngine.h"
#include<iostream>

#include<algorithm>
#include<iterator>

using namespace std;

vector<bool> shuffle(int sum, int mines) {
	vector<bool> v(sum,0);
	back_insert_iterator<std::vector<bool> > p = back_inserter(v);
	for (int i = 0; i < mines; ++i) {
		*p = 1;
	}
	random_shuffle(v.begin(), v.end());
	return v;
}


bool MinesweeperEngine::initBricks(int rows, int cols, int mineSum) {
	normalBrickSum = rows* cols;
	if (normalBrickSum == 0 || mineSum ==0 || mineSum > normalBrickSum) {
		return false;
	}
	this->mineSum = mineSum;
	if (bricks && (this->rows != rows || this->cols != cols)) {
		free(bricks);
		bricks = NULL;
	}
	this->rows = rows;
	this->cols = cols;

	resetEngine();
	return true;
};
void MinesweeperEngine::resetEngine() {
	gameStatus = GameStatus::UNDERWAY;
	flagBrickSum = 0;
	if (!bricks) {
		bricks = (Brick*)malloc(normalBrickSum * sizeof(Brick));
	}
	vector<bool> mineMap = shuffle(normalBrickSum,mineSum);
	for (int j = 0; j < rows; j++)
	{
		for (int i = 0; i < cols; i++)
		{
			int index = j * cols + i;
			Brick* tmpBrick = bricks + index;
			tmpBrick->x = j;
			tmpBrick->y = i;
			tmpBrick->brickStatus = BrickStatus::NORMAL;
			tmpBrick->isMine = mineMap.at(index);
		}
	}

	for (int j = 0; j < rows; j++)
	{
		for (int i = 0; i < cols; i++)
		{
			int index = j * cols + i;
			Brick* tmpBrick = bricks + index;
			if (!tmpBrick->isMine) {
				tmpBrick->mineNumber = getNeighbourMineCount(i,j);
			}
		}
	}
	
	
};

bool MinesweeperEngine::clickBrick(int x, int y, BrickClickEnum ctype) {
	return true;
};
GameStatus MinesweeperEngine::getGameStatus() {
	return gameStatus;
};
BrickStatus MinesweeperEngine::getBrickStatus(int x, int y) {
	int index = x  + y * cols;
	auto it = bricks + index;
	return it->brickStatus;
};
Brick MinesweeperEngine::getBrick(int x, int y) {
	int index = x + y * cols;
	auto it = bricks + index;
	return *it;
};
void MinesweeperEngine::gameLoss() {
	gameStatus = GameStatus::LOSS;
};


std::vector<Brick*> MinesweeperEngine::getNeighbourBrick(int x, int y) {
	std::vector<Brick*> neighbourBricks;
	for (int i = x-1; i <= x+1; i++)
	{
		for (int j = y-1; j <= y+1; j++)
		{
			if (i >= 0 && i < cols && j >= 0 && j < rows) {
				int index = i  + j* cols;
				neighbourBricks.push_back(bricks + index);
			}

		}

	}
	return neighbourBricks;
};
std::vector<Brick*> MinesweeperEngine::getNeighbourBrick(int x, int y, BrickStatus status) {
	std::vector<Brick*> result;
	std::vector<Brick*> neighbourBricks = getNeighbourBrick(x,y);
	for (auto it : neighbourBricks)
	{
		if (it->brickStatus == status) {
			result.push_back(it);
		}
	}
	return result;
};

bool MinesweeperEngine::isNeighbourFlagEqualNumber(int x, int y) {
	int index = x + y * cols;
	auto it = bricks + index;
	return getNeighbourBrick(x, y, BrickStatus::FLAG).size() == it->mineNumber;
};
void MinesweeperEngine::clickNeighbourBrick(int x, int y) {};

int MinesweeperEngine::getNeighbourMineCount(int x, int y) {
	std::vector<Brick*> neighbourBricks = getNeighbourBrick(x,y);
	int count = 0;
	for (auto it : neighbourBricks)
	{
		if (it->isMine) {
			count++;
		}
	}
	return count;
};

MinesweeperEngine::MinesweeperEngine()
{
}

MinesweeperEngine::~MinesweeperEngine()
{
	if (bricks) {
		free(bricks);
		bricks = NULL;
	}
}