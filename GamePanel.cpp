#include "GamePanel.h"
GamePanel::GamePanel(QWidget* widget) :
	QWidget(widget),
	ui(new Ui::GamePanel)
{
	ui->setupUi(this);
};
GamePanel::~GamePanel() {

};
void GamePanel::init() {
};