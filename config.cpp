#include "config.h"

Config * Config::singleton = nullptr;

Config::Config(QObject *parent) : QObject(parent)
{
    settings = new QSettings(QSettings::IniFormat,
                             QSettings::UserScope,"ZED", "Offline Launcher");
}

Config *Config::instance()
{
    if(singleton == nullptr) {
        singleton = new Config();
    }
    return singleton;
}

void Config::setLastPath(QString fileName)
{
    settings->setValue("Last Path", fileName);
    settings->sync();
}

QString Config::lastPath()
{
    return settings->value("Last Path", "").toString();
}

void Config::setProgList(QStringList progs)
{
    QVariant list;
    list.setValue(progs);
    settings->setValue("Prog List", list);
    settings->sync();
}

QStringList Config::progList()
{
    QStringList list;

    list = settings->value("Prog List", list).toStringList();
    return list;
}

