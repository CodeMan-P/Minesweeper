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
class BrickWidget : public QWidget
{
	Q_OBJECT
public:

	explicit BrickWidget::BrickWidget(QWidget* parent = nullptr);
	~BrickWidget();
	void init();
	
private:
	QPixmap paintWidget();
	//鼠标按下事件
	void mousePressEvent(QMouseEvent* event);
	void paintEvent(QPaintEvent* event);
	
public slots:
	//pass
public:
	//pass
};