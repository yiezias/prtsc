
#include "display.h"
#include <QApplication>
#include <QScreen>
#include <QWidget>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	QScreen *sc = QApplication::primaryScreen();
	QPixmap p = sc->grabWindow(0);
	display widget(&p);
	widget.showFullScreen();
	return a.exec();
}
