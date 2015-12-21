#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QApplication>
#include <QWidget>
#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>

class SystemTray : public QObject
{
    Q_OBJECT
public:
    explicit SystemTray(QApplication * application, QWidget * widget, QObject *parent = 0);
    ~SystemTray();
    void show();

    void P_running(QString programName);

    void initMenu();

signals:

public slots:
    void onHide();
    void onDoubleClicked(QSystemTrayIcon::ActivationReason reason);


protected:
    QApplication * application;
    QSystemTrayIcon *Tray = 0;
    QMenu *Menu = 0;
    QAction * closeAction = 0;
    QWidget *widget = 0;
    QAction *showAction = 0;
    QAction *addProgramAction = 0;

    bool messageShown = false;
};

#endif // SYSTEMTRAY_H
