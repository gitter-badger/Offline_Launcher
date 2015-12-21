#ifndef PROGRAMS_H
#define PROGRAMS_H
#include <QList>
#include "program.h"

class Programs
{
public:
    Programs();
    Program *addProgram(QString fileName);
    QList<Program*> *getPrograms();
    Program * getProgram(QString name);
    void deleteProgram(int index);
    void load();
    void save();

protected:
    QList<Program*> *programs;

};

#endif // PROGRAMS_H
