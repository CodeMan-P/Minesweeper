#include "Minesweeper.h"
#include <QtWidgets/QApplication>
void registerPluginsDir()
{
	QString pluginsPath = QCoreApplication::applicationDirPath() + "/plugins/";
	QString platformsPath = QCoreApplication::applicationDirPath() + "/plugins/platforms/";
	QStringList pathes = QCoreApplication::libraryPaths();
	pathes << pluginsPath;
	pathes << platformsPath;
	QCoreApplication::setLibraryPaths(pathes);
}
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	registerPluginsDir();
	Minesweeper w;
	w.show();
	return a.exec();
}
