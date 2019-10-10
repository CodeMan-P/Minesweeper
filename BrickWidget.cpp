#include "BrickWidget.h"
BrickWidget::BrickWidget(QWidget* parent) {

};
BrickWidget::~BrickWidget() {
};
void BrickWidget::init() {

};
void BrickWidget::mousePressEvent(QMouseEvent* event) {

};

QPixmap BrickWidget::paintWidget()
{
	

	QPixmap pixmap(this->width(), this->height());
	QPainter p_painter(&pixmap);
	QPen pen;

	//·´¾â³İ
	p_painter.setRenderHint(QPainter::Antialiasing);
	pixmap.fill(Qt::white);

	
	return pixmap;

}
void BrickWidget::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	QWidget* p = (QWidget*)this->parent();

	painter.setRenderHint(QPainter::Antialiasing);
	painter.drawPixmap(0, 0, this->width(), this->height(), paintWidget());

};