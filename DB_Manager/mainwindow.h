#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "common.h"

namespace Ui {
class MainWindow;
}
enum eFormStyle
{
    Defaut = 0,
    Browse = 1,
    ShowChildForm = 2,
    Delete = 3,
    Edit = 10,
    Add = 11,
    Update = 12
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    eFormStyle m_FormStyle;
};

#endif // MAINWINDOW_H
