#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "maininfo.h"
#include <QGraphicsProxyWidget>
#include "battlescene.h"
#include "skill.h"
#include "player.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),player(new Player())
{
    ui->setupUi(this);
    initUi();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUi()
{
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->graphicsView->setBackgroundBrush(QPixmap(":/image/Time-For-Lunch-2.jpg"));
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    ui->stackedWidget->setCurrentWidget(ui->page_menu);
}

void MainWindow::on_btnBattle_clicked()
{
    if(player->hasTeam())
    {
        PokemonPtr poke2= PokemonPtr(new Pokemon(3));
        ui->stackedWidget->setCurrentWidget(ui->page_battle);
        BattleScene *scene =new BattleScene (player->getFirstPokemon(),poke2);
        ui->graphicsView->setScene(scene);
    }
    else
    {
        qDebug("No team.Can't battle!");
    }
}

void MainWindow::on_btnAddPokemon_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_test_add);
}

void MainWindow::on_btnViewPokemon_clicked()
{
    player->easyViewTeam();
}

void MainWindow::on_pushButton_clicked()
{
    int id = ui->lineEdit->text().toInt();
    PokemonPtr poke= PokemonPtr(new Pokemon(id));
    player->addPokemonToTeam(poke);
    SkillPtr skill =SkillPtr(new NormalSkill("asd","10301"));
    player->learnSkill(0,skill);
}

void MainWindow::on_btnBack_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_menu);
}

void MainWindow::on_btnBack2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_menu);
}

void MainWindow::on_btnAddSkill_clicked()
{
    int index =ui->lineEdit_Id->text().toInt();
    QString name = ui->lineEdit_SkillName->text();
    int power = ui->lineEdit_SkillPower->text().toInt();
    SkillAtkMode mode;
    if(ui->checkBox->isChecked())
        mode=SkillAtkMode::physical;
    else
        mode=SkillAtkMode::special;
    SkillPtr skill =SkillPtr(new NormalSkill(name,PokemonAttribute::water,mode,power));
    player->learnSkill(index,skill);
}

void MainWindow::on_pushButton_4_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_add_skil);
}
