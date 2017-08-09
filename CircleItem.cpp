#include "CircleItem.h"
#include <QCursor>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <Qpainter>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
qreal CircleItem::vecLenSqu(const CircleItem::vec_t & vec)
{
	return vec.x()*vec.x() + vec.y()*vec.y();
}
void CircleItem::limitVec(CircleItem::vec_t & vec, qreal len)
{
	auto x = vec.x(),y = vec.y();

	auto vecLenSqu = x*x + y*y;
	if (vecLenSqu > len*len)
	{
		qreal ratio = len / sqrt(vecLenSqu);
		vec.setX(x*ratio);
		vec.setY(y*ratio);
	}

}

CircleItem::CircleItem(qreal rad, QColor c, QGraphicsItem * parent) :QGraphicsEllipseItem(0, 0, rad, rad, parent)
{
	setPen(QPen(Qt::transparent,0));
	setBrush(c);
	setAcceptHoverEvents(true);
	setFlags(ItemIsMovable  | ItemSendsGeometryChanges);
	mParent = nullptr;
}


void CircleItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	painter->setCompositionMode(QPainter::CompositionMode_Plus);
	QGraphicsEllipseItem::paint(painter, option, widget);
}

QColor CircleItem::color() const
{
	return brush().color();
}

void CircleItem::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	setCursor(Qt::SizeAllCursor);
	mOldMousePoint = mCurrentMousePoint = event->scenePos();
	mOffset = event->scenePos() - pos();
	QGraphicsEllipseItem::mousePressEvent(event);
}

void CircleItem::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
	setCursor(Qt::PointingHandCursor);
	QGraphicsEllipseItem::mouseReleaseEvent(event);
}

void CircleItem::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
	auto mousePos = event->scenePos();
	auto myPos = this->scenePos();
	mAcc = mousePos - myPos - mOffset;
	limitVec(mAcc, 1);
	mVel += mAcc;
	limitVec(mVel,3);
	QGraphicsItem::mouseMoveEvent(event);
}


void CircleItem::hoverEnterEvent(QGraphicsSceneHoverEvent * event)
{
		setCursor(Qt::PointingHandCursor);
		qDebug() << "mouse hover";
		QGraphicsEllipseItem::hoverEnterEvent(event);
}


void CircleItem::hoverLeaveEvent(QGraphicsSceneHoverEvent * event)
{
	setCursor(Qt::ArrowCursor);
	qDebug() << "mouse leave";
	QGraphicsEllipseItem::hoverLeaveEvent(event);
}


QVariant CircleItem::itemChange(GraphicsItemChange change, const QVariant & value)
{
	//from Qt Doc
	if (change == ItemPositionChange && scene()) {
		// value is the new position.
		auto newPos = value.toPointF();

		auto  allViews = this->scene()->views();
		
		if (!allViews.empty())
		{
			auto firstView = allViews[0];
			QRectF rect = firstView->rect();
			if ( newPos.x() > rect.width())
				newPos.setX(-diameter());
			if ( newPos.x()< -diameter())
				newPos.setX(rect.width());
			if ( newPos.y() > rect.height())
				newPos.setY(-diameter());
			if (newPos.y()< -diameter())
				newPos.setY(rect.height());
					return newPos;
		}
	}
	return QGraphicsItem::itemChange(change, value);
	
}


qreal CircleItem::diameter() const
{
	return rect().width();
}