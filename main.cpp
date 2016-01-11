#include "widget.h"
#include <QApplication>
#include <QStyleFactory>
#include <QProcess>
#include "systemtray.h"
//#include "vld.h"

SystemTray *tray = nullptr;
Widget *w = nullptr;

void runAsAutostart(QApplication &a){
    w = new Widget();

    tray = new SystemTray(&a, w);
    tray->show();
}

void runAsNormal(QApplication &a){
    w = new Widget();
    w->show();

    tray = new SystemTray(&a, w);
    tray->show();
}

void runProgram(QApplication &a, QString program){

    // firewall block
    QProcess::execute(program);
    // firewall unblock
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    if(argc == 2){
        if(a.arguments().at(1) == "--autostart"){
            runAsAutostart(a);
        }else{
            runProgram(a, a.arguments().at(1));

            return 0;
        }
    }else if(argc == 3){
        // ...
    }else{
        runAsNormal(a);
    }

	int retVal = a.exec();
    if(tray != nullptr)
        delete tray;
    if(w != nullptr)
        delete w;
    return retVal;
}
