#include "firewall.h"
#include <QFileInfo>
#include <QProcess>
#include <QDebug>
#include <QMessageBox>

Firewall::Firewall(Program *program)
{
    this->program = program;
}

void Firewall::block()
{

    QString filename = program->getFileName();
    QFileInfo fi(filename);
    QString name = fi.baseName();  // base = "archive"
    QString command = QString("netsh advfirewall firewall delete rule name=\"temp%1\""
                              " program=\"%2\"").arg(name).arg(filename.replace("/", "\\"));

    QProcess::execute(command);

    command = QString("netsh advfirewall firewall add rule name=\"temp%1\""
                              " dir=out action=block program=\"%2\" enable=yes").arg(name).arg(filename.replace("/", "\\"));

    QProcess process;
    process.start(command);
    if (!process.waitForStarted())
        return;

    if (!process.waitForFinished())
        return;
    QString result = QString::fromUtf8(process.readAll());
if(!result.startsWith("OK"))
    QMessageBox::warning(0, "Block not possible", result);
}
void Firewall::unblock()
{
    QString filename = program->getFileName();
    QFileInfo fi(filename);
    QString name = fi.baseName();  // base = "archive"

    QString command = QString("netsh advfirewall firewall delete rule name=\"temp%1\""
                              " program=\"%2\"").arg(name).arg(filename.replace("/", "\\"));

    QProcess::execute(command);

    command = QString("netsh advfirewall firewall add rule name=\"temp%1\""
                              " dir=out action=allow program=\"%2\" enable=yes").arg(name).arg(filename.replace("/", "\\"));
    qDebug() << command;
    QProcess process;
    process.start(command);
    if (!process.waitForStarted())
        return;

    if (!process.waitForFinished())
        return;

    QString result = QString::fromUtf8(process.readAll());
if(!result.startsWith("OK"))
    QMessageBox::warning(0, "unblock", result);
}
