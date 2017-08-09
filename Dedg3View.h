#ifndef _DEDG3VIEW_H_
#define _DEDG3VIEW_H_
#include <QGraphicsView>
#include <common.h>
class Dedg3View : public QGraphicsView
{
	Q_OBJECT
public:
	Dedg3View(QWidget *parent = 0);
	void calc();

protected:
	void mouseReleaseEvent(QMouseEvent * event);
	void  wheelEvent(QWheelEvent * event);
	void drawBackground(QPainter * painter, const QRectF & rect);
	

private:
	QTimer * mCalcTimer;
};

#endif