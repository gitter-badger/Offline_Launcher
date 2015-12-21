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
}

QString Config::lastPath()
{
    return settings->value("Last Path", "").toString();
}

