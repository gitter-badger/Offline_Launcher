#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPixmap>
#include "programs.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:

    explicit Widget(QWidget *parent = 0);
    ~Widget();

signals:
    void hiding();

public slots:

    void updateProgramList();
    void initMenu();
    void addProgram();
    void setStartWithWindows(bool start);

protected:

    virtual void closeEvent(QCloseEvent * event);
    virtual void keyPressEvent(QKeyEvent * event);

    bool alreadyExists(QString fileName);

      QAction * startWithWindowsAction;

      void initAutostart();
private slots:

    void on_toolButton_clicked();

    void on_Del_clicked();

    void on_FilePath_clicked();

    void on_startProgram_clicked();

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    Programs programs;
};

#endif // WIDGET_H
