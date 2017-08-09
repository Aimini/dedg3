#ifndef _QT_COMMON_H_
#define _QT_COMMON_H_

#include <QGraphicsScene>
#include <QGraphicsView>
#include <random>
#include <functional>
#include "common.h"
#include "Dedg3View.h"
#include "Dedg3Scene.h"
#include "CircleItem.h"
class QtFactory
{
public:
	static QGraphicsScene * getGraphicsScene()
	{
		QGraphicsScene * scene = new Dedg3Scene();

		//scene->setBackgroundBrush(QColor(0, 0, 0,0));

		//gradient2.setSpread(QGradient::RepeatSpread);
		
		scene->setBackgroundBrush(Qt::black);
		return scene;
	}

	static QGraphicsView * getGraphicsView()
	{
		return new Dedg3View();
		//return new QGraphicsView();
	}


	static CircleItem * getRadomCircleItem()
	{
		
		std::random_device rd;
		std::default_random_engine e(rd());
		
		const int rgbArry[] = { 0xFF8800, 0x0088FF, 0x666666 };
		std::uniform_int_distribution<> radRGB(0, ARR_LEN(rgbArry) - 1);
		std::uniform_int_distribution<> radDia(20, 240);
		int daimeter = radDia(e);
		QColor c(rgbArry[radRGB(e)]);
		c.setAlphaF(0.35);
		CircleItem * item = new CircleItem(daimeter, c);
		item->mVel = QPointF(250 / daimeter, 250 / daimeter);
		return item;
	}

	static void generateCirleInView(QGraphicsView * view)
	{
		qreal x = 0, y = 0, dia = 0, maxDia = 0;
		qDebug() << CPP_COM_VAL(view->size());
		for (uint i = 0; i < 500; ++i)
		{
			CircleItem * one = QtFactory::getRadomCircleItem();
			dia = one->diameter();
			//这一行放不下就放下一行

			if (x + dia >= view->width())
			{
				x = 0;
				y = y + maxDia + 10;
				maxDia = 0;

			}
			if (y+ dia >= view->height())
			{
				y =0;
			}

			if (one->pos().x() + one->diameter() >= view->width())
			{
				qDebug() << "";
			}
			if (dia > maxDia)
				maxDia = dia;

			//这一行放不下就放下一行
			one->setPos(x, y);
			x = x + dia + 10;
			view->scene()->addItem(one);
		}
	}
};
#endif