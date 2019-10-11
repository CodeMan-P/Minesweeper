#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Minesweeper.h"
#include "Mglobal.h"
class Minesweeper : public QMainWindow
{
	Q_OBJECT

public:
	Minesweeper(QWidget *parent = Q_NULLPTR);

private:
	void init();
	void start();
	void setBricks(int row, int cols, int n=0);
	Ui::MinesweeperClass ui;
};
