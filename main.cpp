#include "widget.h"
#include <QApplication>
#include <QStyleFactory>
#include "systemtray.h"
//#include "vld.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    Widget w;
    w.show();

    SystemTray *tray = new SystemTray(&a, &w);
    tray->show();

	int retVal = a.exec();
	delete tray;
    return retVal;
}
