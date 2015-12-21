#ifndef FIREWALL_H
#define FIREWALL_H

#include <QObject>
#include "program.h"

class Firewall
{
public:
    explicit Firewall(Program *program);

    void block();
    void unblock();

protected:
    Program *program;

};

#endif // FIREWALL_H
