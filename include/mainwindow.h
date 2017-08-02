#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtWidgets>
#include <QtCore/qmath.h>
#include <QtCore/qstate.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
//    QList<Pixmap *> items;
//    QStateMachine states;
//    QTimer timer;
};

#endif // MAINWINDOW_H
