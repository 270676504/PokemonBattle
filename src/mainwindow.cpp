#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "maininfo.h"
#include <QGraphicsProxyWidget>
#include "battlescene.h"
#include "skill.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initUi();
    //game-new Game();
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
    Pokemon* poke=new Pokemon(3);
    Pokemon* poke2=new Pokemon(5);
    DamageSkill* skill=new DamageSkill(QString("water"),AbstractPokemon::Attribute::water,AbstractSkill::AtkMode::special,80);
    poke->learnSkill(skill);
    BattleScene *scene =new BattleScene (poke,poke2);
    ui->graphicsView->setScene(scene);
}
