#include "Dedg3View.h"
#include <QTimer>
#include <QGLWidget>
#include <QMouseEvent>
#include <QDebug>
#include "QtFactory.h"
Dedg3View::Dedg3View(QWidget *parent)
	:QGraphicsView(parent)
{
	setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
	setStyleSheet(QString::fromUtf8("border:0px solid gray"));
	mCalcTimer = new QTimer;
#ifndef QT_NO_OPENGL
	this->setViewport(new QGLWidget(QGLFormat( QGL::SampleBuffers )));
#endif
	QObject::connect(mCalcTimer, &QTimer::timeout, this, &Dedg3View::calc);
	mCalcTimer->start(10);
}


void Dedg3View::calc()
{
	auto allItems = items();
	auto grabberItem = static_cast<CircleItem *>(scene()->mouseGrabberItem());
	for (auto oneItemNoCast = allItems.begin(); oneItemNoCast != allItems.end(); ++oneItemNoCast)
	{
		auto oneItem = static_cast<CircleItem *>(*oneItemNoCast);
		auto itemPos = oneItem->pos();
		oneItem->mAcc.setX(0);
		oneItem->mAcc.setY(0);
		for (auto secondItemNoCast = oneItemNoCast + 1; secondItemNoCast != allItems.end(); ++secondItemNoCast)
		{
			auto secondItem = static_cast<CircleItem *>(*secondItemNoCast);
			if (CircleItem::vecLenSqu(itemPos - secondItem->pos()) < std::pow(oneItem->diameter(), 2) * 1.44)
			{
				if ((oneItem->mParent != nullptr || oneItem == grabberItem) &&
					secondItem->mParent == nullptr &&   secondItem != grabberItem)
				{
					secondItem->mParent = oneItem;
				}
				if ((secondItem->mParent != nullptr || secondItem == grabberItem) &&
					oneItem->mParent == nullptr &&   oneItem != grabberItem)
				{
					oneItem->mParent = secondItem;
				}
			}
		}

		if (oneItem->mParent != nullptr &&
			CircleItem::vecLenSqu(itemPos - oneItem->mParent->pos()) > std::pow(oneItem->mParent->diameter() / 2, 2))
		{
			CircleItem::vec_t force = (itemPos - oneItem->mParent->pos())*(-0.1);
			oneItem->mAcc = force / (oneItem->diameter());
			oneItem->mVel =(oneItem->mVel + oneItem->mAcc)*0.98;
			CircleItem::limitVec(oneItem->mVel, 14);
			oneItem->setPos(itemPos + oneItem->mVel);
		}
		else if (grabberItem != oneItem)
		{
			CircleItem::limitVec(oneItem->mAcc, 1);
			oneItem->mVel += oneItem->mAcc;
			if (oneItem->mVel.x()*oneItem->mVel.x() + oneItem->mVel.y()*oneItem->mVel.y()  > 0.5 * 0.5) {
				oneItem->mVel*=0.99;
		}
		oneItem->setPos(itemPos + oneItem->mVel);
			
		}
		else
		{
			qDebug() << "catch focusItem";
		}
		/*itemPos = oneItem->pos();
		if (itemPos.x() + oneItem->diameter() >= this->width() || 
			itemPos.x() <= 0)
		{
			oneItem->mVel.setX( -oneItem->mVel.x());
			oneItem->mAcc.setX(-oneItem->mAcc.x());
		}
		if (itemPos.y() + oneItem->diameter() >= this->height() || 
			itemPos.y() <= 0)
		{
			oneItem->mVel.setY(-oneItem->mVel.y());
			oneItem->mAcc.setY(-oneItem->mAcc.y());
		}*/
	}


}


void  Dedg3View::mouseReleaseEvent(QMouseEvent * event)
{
	for (auto oneItemNoCast : items())
	{
		static_cast<CircleItem *>(oneItemNoCast)->mParent = nullptr;
	}
	QGraphicsView::mouseReleaseEvent(event);
}

void  Dedg3View::wheelEvent(QWheelEvent * event)
{

}


void Dedg3View::drawBackground(QPainter * painter, const QRectF & rect)
{
	QGraphicsView::drawBackground(painter, rect);
}
