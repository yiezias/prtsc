#include "display.h"
#include <QFileDialog>
#include <QMouseEvent>
#include <QPainter>
#include <QTime>

display::display(QPixmap *pi) : pix(pi) {
	pbeg = pix->rect().topLeft();
	pend = pix->rect().bottomRight();
}

void display::paintEvent(QPaintEvent *event) {
	Q_UNUSED(event);
	setCursor(Qt::CrossCursor);
	QPainter painter(this);
	painter.drawPixmap(0, 0, *pix);
	painter.fillRect(pix->rect(), QColor(0, 0, 0, 150));
	if (point != nullptr) {
		QRect rect(pbeg, pend);
		QPixmap out = pix->copy(rect);
		painter.drawPixmap(pbeg * width() / pix->width(), out);
	}
}

void display::mouseDoubleClickEvent(QMouseEvent *event) {
	Q_UNUSED(event);
	save();
}

void display::mouseMoveEvent(QMouseEvent *event) {
	if (point != nullptr) {
		pbeg.setX(qMin(point->x(), event->pos().x())
			  * pix->rect().width() / width());
		pbeg.setY(qMin(point->y(), event->pos().y())
			  * pix->rect().width() / width());
		pend.setX(qMax(point->x(), event->pos().x())
			  * pix->rect().width() / width());
		pend.setY(qMax(point->y(), event->pos().y())
			  * pix->rect().width() / width());
	}
	update();
}

void display::mouseReleaseEvent(QMouseEvent *event) {
	static QPoint p;
	if (point == nullptr) {
		p = event->pos();
		point = &p;
		setMouseTracking(true);
	} else {
		save();
	}
}
#ifdef Q_OS_WIN
#define PRE (getenv("USERPROFILE") + QString("\\"))
#pragma warning(disable : 4996)
#endif
#ifdef Q_OS_LINUX
#define PRE (getenv("HOME") + QString("/"))
#endif

void display::save() {
	QString default_f = QDate::currentDate().toString() + " "
			    + QTime::currentTime().toString() + ".png";
	default_f.replace(":", "_");
	default_f.replace(" ", "_");
	QString filename = QFileDialog::getSaveFileName(
		this, "", PRE + default_f, "PNG Files(*.png)");
	if (filename != "") {
		pix->copy(QRect(pbeg, pend)).save(filename);
	}
	close();
}
