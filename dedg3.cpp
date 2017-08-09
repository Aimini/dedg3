#include "dedg3.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QDebug>
#include <QResizeEvent>
#include "QtFactory.h"
dedg3::dedg3(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);
	scene = QtFactory::getGraphicsScene();


	view = QtFactory::getGraphicsView();
	//view->setParent(this);
	//������һ�䣬view��Ҳ���������½��ˣ����һ��Զ���Ӧ�����ڴ�С
	view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	//view->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored));
	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	
	setCentralWidget(view);
	view->setScene(scene);


	QSize uns(1440, 900);
	resize(uns);
	view->resize(uns);
}

dedg3 * dedg3::create()
{
	dedg3 * d = new dedg3();
	QtFactory::generateCirleInView(d->view);
	return d;
}


void dedg3::resizeEvent(QResizeEvent * event)
{
	//view->update();
	qDebug() << "-----------------";
	qDebug() << CPP_COM_VAL(view->pos());
	
	qDebug() << CPP_COM_VAL(view->size());
	qDebug() << CPP_COM_VAL(scene->sceneRect());
	QWidget::resizeEvent(event);
	

}


dedg3::~dedg3()
{
}
