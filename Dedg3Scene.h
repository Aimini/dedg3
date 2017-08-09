#ifndef _DEDG3SCENE_H_
#define _DEDG3SCENE_H_
#include <QGraphicsScene>
class Dedg3Scene: public QGraphicsScene
{
	public:
		Dedg3Scene(QObject * parent = 0);

protected:
	void drawBackground(QPainter * painter, const QRectF & rect);
};
#endif 