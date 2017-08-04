#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtCore/qmath.h>
#include <QtCore/qstate.h>
#include "game.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initUi();
private:
    Ui::MainWindow *ui;
    Game* game;
};

#endif // MAINWINDOW_H
