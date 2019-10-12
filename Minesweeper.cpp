#include "windows.h"
#include "Minesweeper.h"
int brickRows = 9;
int brickCols = 9;
int mines = 16;
Minesweeper::Minesweeper(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	init();
}
void Minesweeper::init() {
	
	connect(ui.gamePage->ui->returnButton, &QPushButton::clicked, [=]() {
		ui.stackedWidget->setCurrentIndex(0);
		ui.gamePage->slotStop();
		});

	connect(ui.x9, &QPushButton::clicked, [=]() {
		setBricks(9,9);
		});

	connect(ui.x16, &QPushButton::clicked, [=]() {
		setBricks(16,16);
		});

	connect(ui.x16x32, &QPushButton::clicked, [=]() {
		setBricks(16, 32);
		});
	
	connect(ui.customButton, &QPushButton::clicked, [=]() {
		setBricks(ui.rowBox->value(), ui.colBox->value(), ui.minBox->value());
		});
};
void Minesweeper::setBricks(int row,int cols,int n) {
	
	brickRows = max(row, 2);
	brickCols = max(cols,2);
	if (n<=0) {
		mines = brickRows * brickCols * 0.2;
	}
	else if (n>= brickRows * brickCols) {
		mines = brickRows * brickCols;
	}
	else
	{
		mines = n;
	}
	start();
}
void Minesweeper::start() {
	ui.gamePage->init();
	ui.stackedWidget->setCurrentIndex(1);
};