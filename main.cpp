#include "widget.h"
#include <QApplication>
#include <QStyleFactory>
#include <QProcess>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include "systemtray.h"
#include "firewall.h"
#include <QSharedMemory>
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

void runProgram(QApplication &a, QString filename){

    Program program(filename);
    Firewall firewall(&program);
    firewall.block();
    // firewall block

    QProcess *process = new QProcess();

    QFileInfo fileInfo(filename);
    QString dir = fileInfo.dir().absolutePath();
    process->setWorkingDirectory(dir);
    process->start(filename);
    // firewall unblock#
    firewall.unblock();
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QSharedMemory shared("62d60669-bb94-4a94-88bb-b964890a7e04");

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
        if( !shared.create( 512, QSharedMemory::ReadWrite) )
        {
          // For a GUI application, replace this by :
          QMessageBox msgBox;
          msgBox.setText( QObject::tr("Can't start more than one instance of the application.") );
          msgBox.setIcon( QMessageBox::Critical );
          msgBox.exec();
          exit(0);
        }
        runAsNormal(a);
    }

	int retVal = a.exec();
    if(tray != nullptr)
        delete tray;
    if(w != nullptr)
        delete w;
    return retVal;
}
