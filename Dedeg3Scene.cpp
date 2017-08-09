#include "Dedg3Scene.h"
#include "CircleItem.h"
#include <QTimer>
#include <QCursor>
#include <QGraphicsView>
#include <QDebug>

Dedg3Scene::Dedg3Scene(QObject * parent) :QGraphicsScene(parent)
{

}

void  Dedg3Scene::drawBackground(QPainter * painter, const QRectF & rect)
{

	QGraphicsScene::drawBackground(painter, rect);
	QPen p(QColor(111, 111, 111, 86));
	p.setStyle(Qt::SolidLine);
	painter->setPen(p);
	auto allItems = items();
	QVector<QLineF> allLines;
	allLines.reserve(std::pow(allItems.size(), 2) / 2);
	typedef std::tuple<QPointF, qreal, QGraphicsItem *,QGraphicsItem *> CircleDrawData;
	QVector<CircleDrawData> allData;


	for (auto oneItemNoCast : allItems)
	{
		auto oneItem = static_cast<CircleItem *>(oneItemNoCast);
		allData.push_back(std::make_tuple(oneItem->pos(), oneItem->diameter() / 2, oneItem, oneItem->mParent));
	}

	for (uint i = 0; i < allData.size(); ++i)
	 {
		 auto odData = allData[i];
		 for (uint j = i + 1; j < allData.size(); ++j)
		{
			auto osData = allData[j];
			auto oCenPos = std::get<0>(odData) +QPoint(std::get<1>(odData), std::get<1>(odData));
			auto sCenPos = std::get<0>(osData) + QPoint(std::get<1>(osData), std::get<1>(osData));
			if (CircleItem::vecLenSqu(oCenPos - sCenPos) < std::pow(std::get<1>(odData) * 2, 2) * 1.44
				|| std::get<2>(odData) == std::get<3>(osData)
				|| std::get<3>(odData) == std::get<2>(osData))
			{
				allLines.push_back(QLineF(oCenPos, sCenPos));
			}
		}
	}
	painter->drawLines(allLines);
}