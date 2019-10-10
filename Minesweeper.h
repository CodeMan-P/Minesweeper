#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Minesweeper.h"

class Minesweeper : public QMainWindow
{
	Q_OBJECT

public:
	Minesweeper(QWidget *parent = Q_NULLPTR);

private:
	void init();
	void start();
	Ui::MinesweeperClass ui;
};
