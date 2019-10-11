#include "Minesweeper.h"
int brickRows = 9;
int brickCols = 16;
int mines = 30;
Minesweeper::Minesweeper(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	init();
}
void Minesweeper::init() {

	start();
};
void Minesweeper::start() {
	ui.stackedWidget->setCurrentIndex(1);
	ui.gamePage->init();
};