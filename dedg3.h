#ifndef DEDG3_H
#define DEDG3_H

#include <QtWidgets/QMainWindow>
#include "ui_dedg3.h"

class dedg3 : public QMainWindow

{
	Q_OBJECT

public:
	dedg3(QWidget *parent = 0);
	~dedg3();
	
	static dedg3 * create();
protected:
	void resizeEvent(QResizeEvent * event);

private:
	Ui::dedg3Class ui;
	QGraphicsScene *scene;
	QGraphicsView *view;
};

#endif // DEDG3_H
