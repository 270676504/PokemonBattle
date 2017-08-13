#include "battlescene.h"
#include "maininfo.h"
#include <QGraphicsProxyWidget>
#include "graphicsbutton.h"
#include <QPixmap>
#include <QDebug>
#include "skill.h"
#include <QString>
BattleScene::BattleScene(PokemonPtr pokemon1, PokemonPtr pokemon2, QObject *parent)
    :QGraphicsScene(parent),m_pokemon(pokemon1),oppo_pokemon(pokemon2)
{
    setupUi();
}

BattleScene::~BattleScene()
{
    delete m_info;
    delete oppo_info;
}

void BattleScene::changePokemon(PokemonPtr pokemon, BattleScene::Person target)
{
    if(target == Self)
    {
        m_info->changePokemon(pokemon);
    }else{
        oppo_info->changePokemon(pokemon);
    }
}

void BattleScene::setupUi()
{
    m_info = new MainInfo(m_pokemon);
    oppo_info = new MainInfo(oppo_pokemon);

    auto gpWidget=addWidget(m_info);
    gpWidget->setPos(300-m_info->width()/2,100-m_info->height()/2);
    gpWidget=addWidget(oppo_info);
    gpWidget->setPos(-300-oppo_info->width()/2,-200-oppo_info->height()/2);

    //增加技能栏
    QGraphicsItem *skillButtonContainer = new QGraphicsRectItem;
    skillButtonContainer->setTransform(QTransform::fromScale(0.75, 0.75), true);
    skillButtonContainer->setPos(-200, 400);
    skillButtonContainer->setZValue(65);

    QPixmap pix(":/image/image/fire.png");
    QPixmap back(":/image/image/1b.png");
    QPixmap front(":/image/image/1f.png");
    pix=pix.scaled(90,90);
    int m_width=pix.width()+1;
    GraphicsButton *btn1 = new GraphicsButton(/*pix*/ skillButtonContainer);
    GraphicsButton *btn2 = new GraphicsButton(/*pix,*/ skillButtonContainer);
    GraphicsButton *btn3 = new GraphicsButton(/*pix,*/ skillButtonContainer);
    GraphicsButton *btn4 = new GraphicsButton(/*pix,*/ skillButtonContainer);
    btn1->setPos(0-m_width*1.5, 0);
    btn2->setPos(0-m_width/2, 0);
    btn3->setPos(m_width/2, 0);
    btn4->setPos(m_width*1.5, 0);
    addItem(skillButtonContainer);

    //增加敌我图片
    auto item = addPixmap(back);
    item->setPos(-300-pix.width()/2, 100-pix.height()/2);

    item = addPixmap(front);
    item->setPos(200-pix.width()/2, -300+pix.height()/2);

    connect(btn1,&GraphicsButton::pressed,this,[=](){
       m_pokemon->useSkill(0,oppo_pokemon);
       oppo_info->refreshHp();
    });
    connect(btn2,&GraphicsButton::pressed,this,[=](){
        m_pokemon->useSkill(1,oppo_pokemon);
        oppo_info->refreshHp();
    });

    connect(btn3,&GraphicsButton::pressed,this,[=](){
        m_pokemon->useSkill(2,oppo_pokemon);
        oppo_info->refreshHp();
    });

    connect(btn4,&GraphicsButton::pressed,this,[=](){
        m_pokemon->useSkill(3,oppo_pokemon);
        oppo_info->refreshHp();
    });
}
