#include "GamePanel.h"
GamePanel::GamePanel(QWidget* widget) :
	QWidget(widget),
	ui(new Ui::GamePanel)
{
	ui->setupUi(this);
	minesweeperEngine = new MinesweeperEngine();
	ui->gameWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui->gameWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui->gameWidget->setShowGrid(true);
	ui->gameWidget->horizontalHeader()->setVisible(false);
	ui->gameWidget->verticalHeader()->setVisible(false);
};
GamePanel::~GamePanel() {

};
void GamePanel::init() {
	
	
	ui->gameWidget->clear();
	if (minesweeperEngine->initBricks(brickRows, brickCols, mines)) {
		ui->gameWidget->setRowCount(brickRows);
		ui->gameWidget->setColumnCount(brickCols);
		for (int x = 0; x < brickCols; x++)
		{
			
			for (int y = 0; y < brickRows; y++)
			{
				BrickWidget* tmpWidget = new BrickWidget();
				tmpWidget->setNumber(minesweeperEngine->getNeighbourMineCount(x,y));
				ui->gameWidget->setCellWidget(x, y, tmpWidget);
			}
		}
	}
	
	refreshPanel();
};
void GamePanel::refreshPanel() {

	for (int x = 0; x < brickCols; x++)
	{
		for (int y = 0; y < brickRows; y++)
		{
			BrickWidget* brickWidget = (BrickWidget*)(ui->gameWidget->cellWidget(x, y));
			//brickWidget->setStatus(minesweeperEngine->getBrickStatus(x, y));
			
			Brick brick = minesweeperEngine->getBrick(x, y);
			if (brick.isMine) {
				brickWidget->setStatus(BrickStatus::MINE);
			}
			else if (brick.mineNumber != 0) {
				brickWidget->setStatus(BrickStatus::NUMBER);
			}
			else
			{
				brickWidget->setStatus(BrickStatus::EMPTY);
			}
		}
	}

	
};