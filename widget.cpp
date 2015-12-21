#include <QCloseEvent>
#include "widget.h"
#include "config.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QListWidget>
#include <QPixmap>
#include <QDesktopServices>
#include <QUrl>
#include <QDir>
#include <QMessageBox>
#include <QMenu>
#include <QMenuBar>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)

{
    ui->setupUi(this);
    ui->progressBar->setVisible(false);

    programs.load();
    updateProgramList();
    initMenu();


}

Widget::~Widget()
{
    delete ui;
}

void Widget::updateProgramList()
{
    ui->listWidget->clear();
    for(Program *program: programs.getPrograms()->toStdList())
    {

        QString fileName = program->getFileName();
        QListWidgetItem * widgetItem = new QListWidgetItem(fileName);
        widgetItem->setIcon(program->getIcon());
        QColor color;
        switch(program->getStatus())
        {
        case Program::AlwaysActive:

            widgetItem->setTextColor(color.green());
            break;
        case Program::SessionActive:
            widgetItem->setTextColor(color.black());
            break;
        case Program::Deactivated:
            widgetItem->setTextColor(color.red());
            break;
        default:
            widgetItem->setTextColor(color.black());
        }

        ui->listWidget->addItem(widgetItem);
    }

}

void Widget::closeEvent(QCloseEvent * event)
{
    event->ignore();
    this->hide();
    emit hiding();
}

bool Widget::alreadyExists(QString fileName)
{
    for(int i = 0; i < ui->listWidget->count(); ++i)
    {
        if(ui->listWidget->item(i)->text() == fileName)
            return true;
    }
    return false;
}

void Widget::on_toolButton_clicked()
{

    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open File"), Config::instance()->lastPath(),
                                                          tr("Executables (*.exe);; All Files (*.*)"));

    ui->progressBar->setMaximum(fileNames.count());
    ui->progressBar->setValue(0);
    ui->progressBar->setVisible(true);

    for(QString fileName: fileNames){

        ui->progressBar->setValue(ui->progressBar->value() + 1);

        if (!fileName.isNull())
        {
            Config::instance()->setLastPath(QFileInfo(fileName).path()); // store path for next time
        }
        if (fileName.isEmpty())
            return;

        if(alreadyExists(fileName)){
            QMessageBox::information(this, "Already Exists", fileName + " already exists.");
            continue; // insert next item, not this one !
        }

        programs.addProgram(fileName);

        updateProgramList();
        
    }
    ui->progressBar->setVisible(false);
}

void Widget::keyPressEvent(QKeyEvent * event)
{
    if (event->key()== Qt::Key_Delete)
    {
    on_Del_clicked();
    }
}

void Widget::on_Del_clicked()
{

    for(QListWidgetItem *item: ui->listWidget->selectedItems()){
        programs.deleteProgram(ui->listWidget->row(item));
        ui->listWidget->removeItemWidget(item);
        delete item;
    }
    updateProgramList();

}
void Widget::on_FilePath_clicked()
{
    if(ui->listWidget->currentItem() != NULL)
    {
        QString fileName = ui->listWidget->currentItem()->text();

        QStringList args;

        args << "/select," << QDir::toNativeSeparators(fileName);

        QProcess::startDetached("explorer", args);
    }
    else
    {
        QMessageBox::warning(this, "", "Bitte wählen sie einen Eintrag aus der Liste");
    }
}

void Widget::initMenu()
{
    QMenuBar *menuBar = new QMenuBar();
    QMenu *about = new QMenu(tr("&About"), this);
    QMenu *settings = new QMenu(tr("&Settings"), this);
    about->addSeparator();
    menuBar->addMenu(about);
    menuBar->addMenu(settings);

    about->setStyleSheet("QMenu::item:selected {background-color: rgb(51, 153, 255);}");
    settings->setStyleSheet("QMenu::item:selected {background-color: rgb(51, 153, 255);}");

    startWithWindowsAction = settings->addAction("Start with Windows");

    initAutostart();
    about->addAction("Version");
    about->addAction("Check for Update");
    about->addAction("Donate");
    about->addAction("Help");

    this->layout()->setMenuBar(menuBar);
    connect(startWithWindowsAction, SIGNAL(toggled(bool)), this, SLOT(setStartWithWindows(bool)));

}

void Widget::initAutostart(){

    startWithWindowsAction->setCheckable(true);

#ifdef _WIN32
    QSettings registry("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    if(registry.childKeys().contains("Offline Launcher"))
        startWithWindowsAction->setChecked(true);
#endif
}

void Widget::addProgram()
{
    show();
    on_toolButton_clicked();
}

void Widget::setStartWithWindows(bool start)
{
#ifdef _WIN32
    QSettings registry("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    if (start)
    {
        registry.setValue("Offline Launcher", "\"" + QCoreApplication::applicationFilePath().replace("/", "\\") + "\"");
    }else {
        registry.remove("Offline Launcher");
    }
#endif
}



void Widget::on_startProgram_clicked()
{

    for(QListWidgetItem *item: ui->listWidget->selectedItems()){

        QString program = item->text();
        Program * prog = programs.getProgram(program);
        if(prog != 0)
                prog->start();
    }
}

void Widget::on_pushButton_clicked()
{
    for(QListWidgetItem *item: ui->listWidget->selectedItems()){

        QString program = item->text();
        Program * prog = programs.getProgram(program);
        if(prog != 0)
        {
            prog->block();
        }
    }
}
