#ifdef _WIN32
#include <qt_windows.h>
#include <QtWinExtras/QtWinExtras>
#endif

#include "program.h"
#include "firewall.h"

Program::Program(QString fileName)
{
    this->fileName = fileName;
    ico.addPixmap(pixmapFromExecutable(fileName));
    process.setProgram("\"" + fileName + "\"");
}

QPixmap Program::pixmapFromExecutable(QString exe)
{
    QPixmap pixmap;
#ifdef _WIN32
	HINSTANCE hInstance = ::GetModuleHandle(NULL);
#ifdef UNICODE
    wchar_t *convertedName = new wchar_t[exe.length() + 1];
    exe.toWCharArray(convertedName);
    convertedName[exe.length()] = '\0';
    HICON Icon = ::ExtractIcon(hInstance, convertedName, 0);
    delete convertedName;
#else
    HICON Icon = ::ExtractIcon(hInstance, exe.toStdString().c_str(), 0);
#endif
    pixmap = QtWin::fromHICON(Icon);

#endif
    return pixmap;
}

QIcon Program::getIcon()
{
    return ico;
}

QString Program::getFileName()
{
    return fileName;
}

Program::Status Program::getStatus()
{
    return status;
}

void Program::start()
{
    process.start();
}

void Program::block()
{
    Firewall fw(this);
    fw.block();
}

void Program::unblock()
{
    Firewall fw(this);
    fw.unblock();
}
