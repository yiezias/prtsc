#ifndef DISPLAY_H
#define DISPLAY_H
#include <QWidget>


class display : public QWidget {
	Q_OBJECT
	QPixmap *pix;
	QPoint *point = nullptr, pbeg, pend;

public:
	display(QPixmap *pi);
	void paintEvent(QPaintEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void save();

signals:
};

#endif	// DISPLAY_H
