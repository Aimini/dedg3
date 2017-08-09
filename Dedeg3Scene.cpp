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
	typedef std::tuple< CircleItem *, CircleItem *> CircleDrawData;
	QVector<CircleDrawData> allData;


	for (auto oneItemNoCast : allItems)
	{
		auto oneItem = static_cast<CircleItem *>(oneItemNoCast);
		allData.push_back(std::make_tuple(oneItem, oneItem->mParent));
	}

	for (uint i = 0; i < allData.size(); ++i)
	 {
		 auto odData = allData[i];
		 for (uint j = i + 1; j < allData.size(); ++j)
		{
			auto osData = allData[j];
			auto oCenPos = std::get<0>(odData)->centerPos();
			auto sCenPos = std::get<0>(osData)->centerPos();
			if (CircleItem::vecLenSqu(oCenPos - sCenPos) < std::pow(std::get<0>(odData)->diameter()/2, 2) * 1.44
				|| std::get<0>(odData) == std::get<1>(osData)
				|| std::get<1>(odData) == std::get<0>(osData))
			{
				allLines.push_back(QLineF(oCenPos, sCenPos));
			}
		}
	}
	painter->drawLines(allLines);
}