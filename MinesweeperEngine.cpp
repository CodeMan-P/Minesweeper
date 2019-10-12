#include "MinesweeperEngine.h"
#include<iostream>

#include<algorithm>
#include<iterator>
#include<time.h>
using namespace std;

vector<bool> shuffle(int sum, int mines) {
	srand((unsigned)time(NULL));
	vector<bool> v(max(sum - mines,0), 0);
	v.insert(v.end(), mines, 1);
	random_shuffle(v.begin(), v.end());
	return v;
}

void MinesweeperEngine::stop() {
	if (bricks) {
		free(bricks);
		bricks = NULL;
	}
};
bool MinesweeperEngine::initBricks(int rows, int cols, int mineSum) {
	normalBrickSum = rows * cols;
	brickSurpluses = rows * cols;
	if (normalBrickSum == 0 || mineSum == 0 || mineSum > normalBrickSum) {
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
int MinesweeperEngine::getMineNumber() {
	return mineSum - flagBrickSum;
};
int MinesweeperEngine::getBrickSurpluses() {
	return brickSurpluses;
};
void MinesweeperEngine::resetEngine() {
	brickSurpluses = rows * cols;
	gameStatus = GameStatus::UNDERWAY;
	flagBrickSum = 0;
	if (!bricks) {
		bricks = (Brick*)malloc(normalBrickSum * sizeof(Brick));
	}
	vector<bool> mineMap = shuffle(normalBrickSum, mineSum);
#pragma omp parallel for
	for (int j = 0; j < rows; j++)
	{
		for (int i = 0; i < cols; i++)
		{
			int index = j * cols + i;
			Brick* tmpBrick = bricks + index;
			tmpBrick->x = i;
			tmpBrick->y = j;
			tmpBrick->brickStatus = BrickStatus::NORMAL;
			tmpBrick->isMine = mineMap.at(index);

		}
	}
#pragma omp parallel for
	for (int j = 0; j < rows; j++)
	{
		for (int i = 0; i < cols; i++)
		{
			int index = j * cols + i;
			Brick* tmpBrick = bricks + index;
			if (!tmpBrick->isMine) {
				tmpBrick->mineNumber = getNeighbourMineCount(tmpBrick);
			}
			else
			{
				tmpBrick->mineNumber = 10;
			}
		}
	}


};
void MinesweeperEngine::lclickNormal(Brick* brick) {
	brickSurpluses--;
	if (brick->isMine) {
		brick->brickStatus = MINE;
		gameStatus = LOSS;
	}
	else if (brick->mineNumber != 0)
	{
		brick->brickStatus = NUMBER;
	}
	else
	{
		brick->brickStatus = EMPTY;	
	}


}
bool MinesweeperEngine::lclick(Brick* brick) {

	BrickStatus brickStatus = brick->brickStatus;
	switch (brickStatus)
	{
	case EMPTY:
		break;
	case NORMAL:
		lclickNormal(brick);
		if (brick->brickStatus == EMPTY) {
			clickNeighbourBrick(brick);
		}
		return true;
	case SUSPICIOUS:
		break;
	case FLAG:
		break;
	case NUMBER:
		break;
	case MINE:
		break;
	default:
		break;
	}
	return false;
};
bool MinesweeperEngine::rclick(Brick* brick) {

	BrickStatus brickStatus = brick->brickStatus;
	switch (brickStatus)
	{
	case EMPTY:
		break;
	case NORMAL:
		brickSurpluses--;
		flagBrickSum++;
		brick->brickStatus = FLAG;
		return true;
	case SUSPICIOUS:
		brick->brickStatus = NORMAL;
		return true;
	case FLAG:
		brickSurpluses++;
		flagBrickSum--;
		brick->brickStatus = SUSPICIOUS;
		return true;
	case NUMBER:
		break;
	case MINE:
		break;
	default:
		break;
	}
	return false;
};
bool MinesweeperEngine::midclick(Brick* brick) {

	BrickStatus brickStatus = brick->brickStatus;
	switch (brickStatus)
	{
	case NUMBER:
		return clickNeighbourBrick(brick);
	default:
		break;
	}
	return false;
};
bool MinesweeperEngine::clickBrick(int x, int y, BrickClickEnum ctype) {
	int index = x + y * cols;
	Brick* brick = bricks + index;
	
	bool result = false;
	switch (ctype)
	{
	case L:
		result = lclick(brick);
		break;
	case R:
		result = rclick(brick);
		break;
	case MIDDLE:
		result = midclick(brick);
		break;
	}
	refreshGameStatus();
	return result;
};
void MinesweeperEngine::refreshGameStatus() {
	if (gameStatus == LOSS) {
#pragma omp parallel for
		for (int j = 0; j < rows; j++)
		{
			for (int i = 0; i < cols; i++)
			{
				int index = j * cols + i;
				Brick* tmpBrick = bricks + index;
				if (tmpBrick->isMine) {
					tmpBrick->brickStatus = BrickStatus::MINE;
				}
				
			}
		}
		return;
	}
	//cout << flagBrickSum << " " << brickSurpluses << " " << mineSum << endl;
	if (flagBrickSum + brickSurpluses == mineSum) {
		gameStatus = WIN;
	}
};
GameStatus MinesweeperEngine::getGameStatus() {
	return gameStatus;
};
BrickStatus MinesweeperEngine::getBrickStatus(int x, int y) {
	int index = x + y * cols;
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


std::vector<Brick*> MinesweeperEngine::getNeighbourBrick(Brick* brick) {
	std::vector<Brick*> neighbourBricks;
	int x = brick->x;
	int y = brick->y;

	for (int i = x - 1; i <= x + 1; i++)
	{
		for (int j = y - 1; j <= y + 1; j++)
		{
			if (i >= 0 && i < cols && j >= 0 && j < rows) {
				int index = i + j * cols;
				neighbourBricks.push_back(bricks + index);
			}

		}

	}
	return neighbourBricks;
};
std::vector<Brick*> MinesweeperEngine::getNeighbourBrick(Brick* brick, BrickStatus status) {
	std::vector<Brick*> result;
	std::vector<Brick*> neighbourBricks = getNeighbourBrick(brick);
	for (auto it : neighbourBricks)
	{
		if (it->brickStatus == status) {
			result.push_back(it);
		}
	}
	return result;
};

bool MinesweeperEngine::isNeighbourSafe(Brick* brick) {

	return getNeighbourBrick(brick, BrickStatus::FLAG).size() >= brick->mineNumber;
};
bool MinesweeperEngine::clickNeighbourBrick(Brick* brick) {
	/*if (isNeighbourSafe(brick)) {
		std::vector<Brick*> normalBricks = getNeighbourBrick(brick, NORMAL);
		for (auto it : normalBricks)
		{
			clickBrick(it->x, it->y, BrickClickEnum::L);
		}
		return true;
	}*/
	if (isNeighbourSafe(brick)) {
		std::vector<Brick*> normalBricks = getNeighbourBrick(brick, NORMAL);
		
		while (normalBricks.size() != 0)
		{
			Brick* tmpBrick = normalBricks.back();
			normalBricks.pop_back();
			if (tmpBrick->brickStatus == NORMAL) {
				lclickNormal(tmpBrick);
				if (tmpBrick->brickStatus == EMPTY) {
					std::vector<Brick*> tmpBricks = getNeighbourBrick(tmpBrick, NORMAL);
					normalBricks.insert(normalBricks.end(), tmpBricks.begin(), tmpBricks.end());
				}
			}
		}
		return true;
	}
	return false;
};
int MinesweeperEngine::getNeighbourMineCount(int x, int y) {
	int index = x + y * cols;
	auto it = bricks + index;
	return getNeighbourMineCount(it);
}
int MinesweeperEngine::getNeighbourMineCount(Brick* brick) {
	std::vector<Brick*> neighbourBricks = getNeighbourBrick(brick);
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