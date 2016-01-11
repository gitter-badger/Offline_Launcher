#ifndef CONFIG_H
#define CONFIG_H

#include <QtCore>
#include <QObject>
#include <QSettings>
#include <QStringList>

class Config : public QObject
{
    Q_OBJECT
public:
    explicit Config(QObject *parent = 0);

    static Config *instance();

    void setLastPath(QString fileName);

    QString lastPath();

    void setProgList(QStringList progs);

    QStringList progList();


signals:

public slots:

protected:
    QSettings * settings = nullptr;


private:
    static Config * singleton;

};

#endif // CONFIG_H
