#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtCore/qmath.h>
#include <QtCore/qstate.h>

class Player;
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
    Player* player;
};

#endif // MAINWINDOW_H
