#include "programs.h"
#include "config.h"

Programs::Programs()
{
    programs = new QList<Program*>();
}

Program *Programs::addProgram(QString fileName)
{
    Program *program = new Program(fileName);
    programs->append(program);
	return program;
}

QList<Program*> * Programs::getPrograms()
{
    return programs;
}

Program *Programs::getProgram(QString name)
{
    for(Program *program: getPrograms()->toStdList())
    {

        QString fileName = program->getFileName();
        if( fileName == name)
            return program;
    }
    return 0;

}

void Programs::deleteProgram(int index)
{
	Program * program = programs->at(index);
    programs->removeAt(index);
	if(program)
		delete program;
}

void Programs::load()
{
    QStringList list = Config::instance()->progList();
    for(QString app : list){
        addProgram(app);
    }
}

void Programs::save()
{
    QStringList list;
    for(Program *program: getPrograms()->toStdList())
    {
        list << program->getFileName();
    }
    Config::instance()->setProgList(list);
}

