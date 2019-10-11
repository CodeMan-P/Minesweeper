#include "BrickWidget.h"
#include "qDebug"
BrickWidget::BrickWidget(QWidget* parent) {
	
};
BrickWidget::~BrickWidget() {
};
void BrickWidget::init() {

};
//void BrickWidget::mousePressEvent(QMouseEvent* event) {
//	qDebug() << "123";
//};
void BrickWidget::setStatus(BrickStatus status) {
	if (this->brickStatus != status) {
		this->brickStatus = status;
		update();
	}
	
};
void BrickWidget::setNumber(int num) {
	this->number = num;
};
QPixmap BrickWidget::paintWidget()
{
	

	QPixmap pixmap(this->width(), this->height());
	QPainter p_painter(&pixmap);
	QPen pen;
	
	
	//·´¾â³Ý
	p_painter.setRenderHint(QPainter::Antialiasing);
	pixmap.fill(Qt::gray);

	
	

	

	

	switch (brickStatus)
	{
	case EMPTY:
		pixmap.fill(Qt::white);
		break;
	case NORMAL:
		break;
	case SUSPICIOUS:
		p_painter.drawImage(pixmap.rect(), QImage(":/icons/suspicious.png"));
		break;
	case FLAG:
		p_painter.drawImage(pixmap.rect(), QImage(":/icons/flag.png"));
		break;
	case NUMBER:
		pixmap.fill(Qt::white);
		paintNumber(p_painter);
		break;
	case MINE:
		p_painter.drawImage(pixmap.rect(), QImage(":/icons/mine.png"));
		break;
	default:
		break;
	}
	
	
	
	return pixmap;

}
void BrickWidget::paintNumber(QPainter& p_painter) {
	QString str = QString::number(number);
	QFont font;
	
	font.setFamily("Microsoft YaHei");
	font.setLetterSpacing(QFont::AbsoluteSpacing, 0);
	float x = this->width() / 2.0;
	float y = this->height() / 2.0;
	for (int i = 35; i > 0; i--)
	{
		font.setPointSize(i);
		QFontMetricsF fontMetrics(font);
		qreal wid = fontMetrics.width(str);
		qreal hei = fontMetrics.height();
		if (max(hei, wid) <= (this->width() - marginWidth * 2)) {
			p_painter.setFont(font);
			p_painter.drawText(x - wid/2, y + hei / 3, str);
			return;
		}
	}
	
	
}
void BrickWidget::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	QWidget* p = (QWidget*)this->parent();

	painter.setRenderHint(QPainter::Antialiasing);
	painter.drawPixmap(0, 0, this->width(), this->height(), paintWidget());

};