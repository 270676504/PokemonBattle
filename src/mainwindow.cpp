#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "maininfo.h"
#include <QGraphicsProxyWidget>
#include "battlescene.h"
#include "skill.h"
#include "player.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initUi();
    player=new Player();
    PokemonPtr poke= PokemonPtr(new Pokemon(3));
    SkillPtr skill=SkillPtr(new DamageSkill(QString("water"),PokemonAttribute::water,SkillAtkMode::special,80));
    poke->learnSkill(skill);
    player->addPokemonToTeam(poke);
    PokemonPtr poke2= PokemonPtr(new Pokemon(3));
    if(player->hasTeam())
    {
        BattleScene *scene =new BattleScene (player->getFirstPokemon(),poke2);
        ui->graphicsView->setScene(scene);
    }
    else
    {
        qDebug("No team.Can't battle!");
    }
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
}
