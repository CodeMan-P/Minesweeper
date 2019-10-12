#include "GamePanel.h"
#include<iostream>
#include<qDebug>

using namespace std;
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
	this->setFocusPolicy(Qt::StrongFocus);
	ui->gameWidget->viewport()->installEventFilter(this);

	
	ui->timeNumber->setPalette(Qt::red);
	ui->mineNumber->setPalette(Qt::red);

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(refreshTime()));
	
	connect(ui->restartButton, &QPushButton::clicked, [=]() { init(); });
};
void GamePanel::slotStop() {
	minesweeperEngine->stop();
	ui->gameWidget->clear();
}
void GamePanel::refreshTime() {
	
	int msecs = time.elapsed();
	QString timestr;
	timestr = QTime::fromMSecsSinceStartOfDay(msecs).toString(msecs/1000.0 >= 60 * 60 - 1 ? "hh:mm:ss" : "mm:ss");
	
	ui->timeNumber->setDigitCount(timestr.length());
	ui->timeNumber->display(timestr); 
}
GamePanel::~GamePanel() {
	ui->gameWidget->clear();
	if (minesweeperEngine) {
		delete minesweeperEngine;
		minesweeperEngine = NULL;
	}
	if (timer) {
		timer->stop();
		delete timer;
		timer = NULL;
	}
};
bool GamePanel::eventFilter(QObject* obj, QEvent* e) {
	

	if (obj == ui->gameWidget->viewport())
	{
		QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(e);
		if (mouseEvent) {
			BrickClickEnum ctype;
			switch (mouseEvent->type())
			{
			case QMouseEvent::MouseButtonDblClick:
				ctype = BrickClickEnum::MIDDLE;
				clickBrickWidget(mouseEvent->pos(), ctype);
				break;
			case QMouseEvent::MouseButtonRelease:
				switch (mouseEvent->button())
				{
				case Qt::MouseButton::LeftButton:
					ctype = BrickClickEnum::L;
					break;
				case Qt::MouseButton::RightButton:
					ctype = BrickClickEnum::R;
					break;
				case Qt::MouseButton::MidButton:
					ctype = BrickClickEnum::MIDDLE;
					break;
				default:
					break;
				}
				clickBrickWidget(mouseEvent->pos(), ctype);
				break;
			case QMouseEvent::MouseButtonPress:
				break;
			default:
				break;
			}
			
			
		}
		
	}
	return QWidget::eventFilter(obj, e);

};
void GamePanel::clickBrickWidget(QPoint p, BrickClickEnum ctype) {
	
	BrickWidget* widget = (BrickWidget*)ui->gameWidget->childAt(p);
	QModelIndex index = ui->gameWidget->indexAt(p);

	//qDebug() << p << " " << index.column()<<" "<< index.row();
	if (widget) {
		minesweeperEngine->clickBrick(index.column(),index.row(), ctype);
		refreshPanel();
	}
}
void GamePanel::init() {
	timer->stop();
	slotStop();
	if (minesweeperEngine->initBricks(brickRows, brickCols, mines)) {
		ui->gameWidget->clear();
		ui->gameWidget->setRowCount(brickRows);
		ui->gameWidget->setColumnCount(brickCols);
//#pragma omp parallel for
		for (int x = 0; x < brickCols; x++)
		{

			for (int y = 0; y < brickRows; y++)
			{
				BrickWidget* tmpWidget = new BrickWidget();
				tmpWidget->setNumber(minesweeperEngine->getNeighbourMineCount(x, y));
				ui->gameWidget->setCellWidget(y, x, tmpWidget);
			}
		}

	}
	refreshPanel();
	
	ui->timeNumber->display("00:00");
	time.restart();
	timer->start(500);
	
};
void GamePanel::refreshPanel() {
	for (int x = 0; x < brickCols; x++)
	{
		for (int y = 0; y < brickRows; y++)
		{
			BrickWidget* brickWidget = (BrickWidget*)(ui->gameWidget->cellWidget(y, x));
			brickWidget->setStatus(minesweeperEngine->getBrickStatus(x, y));
			
			/*Brick brick = minesweeperEngine->getBrick(x, y);
			if (brick.isMine) {
				brickWidget->setStatus(BrickStatus::MINE);
			}
			else if (brick.mineNumber != 0) {
				brickWidget->setStatus(BrickStatus::NUMBER);
			}
			else
			{
				brickWidget->setStatus(BrickStatus::EMPTY);
			}*/
		}
	}
	
	QString mineNumber = QString::number(minesweeperEngine->getMineNumber());
	ui->mineNumber->setDigitCount(mineNumber.length());
	ui->mineNumber->display(mineNumber);
	
	QApplication::processEvents();
	switch (minesweeperEngine->getGameStatus())
	{
	case WIN:
		QMessageBox::information(NULL, "victory", "Congratulation!!!", QMessageBox::Yes , QMessageBox::Yes);
		init();
		break;
	case LOSS:
		QMessageBox::information(NULL, "loss", "The game failed!!!", QMessageBox::Yes , QMessageBox::Yes);
		init();
		break;
	default:
		break;
	}

};