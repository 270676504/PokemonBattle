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
private slots:
    void on_btnBattle_clicked();

    void on_btnAddPokemon_clicked();

    void on_btnViewPokemon_clicked();

    void on_pushButton_clicked();

    void on_btnBack_clicked();

    void on_btnBack2_clicked();

    void on_btnAddSkill_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    Player* player;
};

#endif // MAINWINDOW_H
