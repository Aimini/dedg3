#include <QGraphicsEllipseItem>
#include <common.h>
#include <math/vector.h>
class CircleItem : public QGraphicsEllipseItem
{
	public:
		typedef QPointF vec_t;
		CircleItem(qreal dia , QColor c = qRgba(250,250,250,0.8), QGraphicsItem * parent = 0);
		QColor color() const;
		qreal diameter() const;

		static void limitVec(vec_t & vec, qreal len);
		static qreal vecLenSqu(const vec_t & vec);
		void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
protected:
	/*	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);*/
		void mousePressEvent(QGraphicsSceneMouseEvent * event);
		void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
		void mouseMoveEvent(QGraphicsSceneMouseEvent * event);

		void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
		void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);

		QVariant itemChange(GraphicsItemChange change, const QVariant & value);

public:
	vec_t mVel;
	vec_t mOffset;
	vec_t mAcc;
	vec_t mOldMousePoint;
	vec_t mCurrentMousePoint;
	CircleItem * mParent;
};


