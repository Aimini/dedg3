#include "dedg3.h"
#include <QtWidgets/QApplication>
#include <QtPlugin> 
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin);
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	dedg3 * w = dedg3::create();	
	
	w->show();

	return a.exec();
}
