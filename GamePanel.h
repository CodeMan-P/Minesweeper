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
#include "ui_GamePanel.h"
#include "MinesweeperEngine.h"
#include "Mglobal.h"
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

private:
	MinesweeperEngine* engine = NULL;
	//QPixmap paintWidget();
	////鼠标按下事件
	//void mousePressEvent(QMouseEvent* event);
	//void paintEvent(QPaintEvent* event);

public slots:
	//pass
public:
	//pass
	

};