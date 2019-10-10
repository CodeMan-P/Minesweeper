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
#include "MinesweeperEngine.h"
class BrickWidget : public QWidget
{
	Q_OBJECT
public:

	explicit BrickWidget::BrickWidget(QWidget* parent = nullptr);
	~BrickWidget();
	void init();
	QPixmap paintWidget();
	void paintEvent(QPaintEvent* event);
	void setStatus(BrickStatus status);
	void setNumber(int num);
private:
	int marginWidth = 2;
	BrickStatus brickStatus;
	int number = 0;
	//鼠标按下事件
	void mousePressEvent(QMouseEvent* event);
	void paintNumber(QPainter& p_painter);
	
public slots:
	//pass

};