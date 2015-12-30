#ifndef PROGRAM_H
#define PROGRAM_H

#include <QProcess>
#include <QIcon>

class Program
{
public:
    enum Status
    {
        AlwaysActive = 0,
        SessionActive,
        Deactivated
    };

    Program(QString fileName);
    QPixmap pixmapFromExecutable(QString exe);

    QIcon getIcon();
    QString getFileName();
    Status getStatus();

    void start();
    void block();
    void unblock();

protected:
    QString fileName;
    QIcon ico;
    Status status = AlwaysActive;
    QProcess process;
};

#endif // PROGRAM_H
