#pragma once
#include <QWidget>
#include <QPixmap>
#include <QMouseEvent>
#include <QPoint>
#include <QPainter>
#include <QImage>
#include <queue>
#include <QPolygon>
#include <mutex>
#include <QTimer>
#include <QDateTime>
#include "ui_GamePanel.h"
#include "MinesweeperEngine.h"
#include "Mglobal.h"
#include "BrickWidget.h"
#include<QMessageBox>
namespace Ui {
	class GamePanel;
}

class GamePanel : public QWidget
{
	Q_OBJECT

public:
	explicit GamePanel::GamePanel(QWidget* parent = nullptr);
	Ui::GamePanel* ui;
	
	~GamePanel();
	void init();
	
	void refreshPanel();

private:
	
	QTime time;
	QTimer* timer;
	std::vector<BrickWidget*> brickWidgets;
	void clickBrickWidget(QPoint p, BrickClickEnum ctype);
	bool eventFilter(QObject* obj, QEvent* e);
	
	MinesweeperEngine* minesweeperEngine = NULL;
	//QPixmap paintWidget();
	////鼠标按下事件
	//void mousePressEvent(QMouseEvent* event);
	//void paintEvent(QPaintEvent* event);

public slots:
	void slotStop();
	void refreshTime();
public:
	//pass
	

};