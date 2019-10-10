#include "MinesweeperEngine.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>

using namespace std;

vector<bool> shuffle(int sum, int mines) {
	vector<bool> v = {0};
	back_insert_iterator<std::vector<bool> > p = back_inserter(v);
	for (int i = 0; i < mines; ++i) {
		*p = 1;
	}
	random_shuffle(v.begin(), v.end());
	return v;
}


MinesweeperEngine::MinesweeperEngine()
{
}

MinesweeperEngine::~MinesweeperEngine()
{
	if (bricks) {
		delete bricks;
		bricks = NULL;
	}
}