#include <QIcon>
#include "systemtray.h"

SystemTray::SystemTray(QApplication * application,QWidget *widget, QObject *parent) : QObject(parent)
{
    this->widget = widget;
    this->application = application;
    initMenu();

    connect(closeAction, SIGNAL(triggered(bool)), application, SLOT(quit()));
    connect(showAction, SIGNAL(triggered(bool)), widget, SLOT(show()));
    connect(addProgramAction, SIGNAL(triggered(bool)), widget, SLOT(addProgram()));
    connect(widget, SIGNAL(hiding()), this, SLOT(onHide()));

    QString filename = ":/Tray";
    QIcon icon(filename);
    Tray = new QSystemTrayIcon(icon);
    Tray->setContextMenu(Menu);

    connect(Tray, SIGNAL(messageClicked()), widget, SLOT(show()));
    connect(Tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(onDoubleClicked(QSystemTrayIcon::ActivationReason)));
}

SystemTray::~SystemTray()
{
    if(Tray)
        delete Tray;
        //Tray->hide();
    if(Menu)
        delete Menu;
}

void SystemTray::show()
{
    P_running("No program");
    Tray->setVisible(true);
    //Tray->showMessage("Offline Launcher", "disconnecting NSA... ",QSystemTrayIcon::Information, 1000);
}


void SystemTray::P_running(QString programName)
{
    Tray->setToolTip("Offline Launcher | " + programName + " running...");
}
void SystemTray::initMenu()
{
    Menu = new QMenu("Settings");
    showAction = Menu->addAction("Show");
    addProgramAction = Menu->addAction("Add program");
    Menu->addAction("Launch...");
    Menu->addAction("Activate");
    Menu->addAction("Deactivate");
    Menu->addSeparator();
    closeAction = Menu->addAction("Close");
}

void SystemTray::onHide()
{
    if(!messageShown)
    {
        messageShown = true;
        Tray->showMessage("Offline Launcher", "is still running in the Taskbar.",QSystemTrayIcon::Information, 1000);
    }
}

void SystemTray::onDoubleClicked(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::DoubleClick)
    {
         widget->show();
         widget->activateWindow();
    }
}
