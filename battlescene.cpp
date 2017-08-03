#include "battlescene.h"
#include "maininfo.h"
#include <QGraphicsProxyWidget>
#include "graphicsbutton.h"
#include <QPixmap>
#include <QDebug>
#include "skill.h"
#include <QString>
BattleScene::BattleScene(QObject *parent)
    :QGraphicsScene(parent)
{
    Pokemon* poke=new Pokemon(3);
    Pokemon* poke2=new Pokemon(5);
    m_info=new MainInfo();
    oppo_info=new MainInfo();
    m_info->setInfo(poke);
    DamageSkill* skill=new DamageSkill(QString("water"),AbstractPokemon::Attribute::water,AbstractSkill::AtkMode::special,80,80,80);
    poke->learnSkill(skill);
    oppo_info->setInfo(poke2);
    //增加属性栏
    //坐标为屏幕中心到info左上角
    auto gpWidget=addWidget(m_info);
    gpWidget->setPos(300-m_info->width()/2,100-m_info->height()/2);
    gpWidget=addWidget(oppo_info);
    gpWidget->setPos(-300-oppo_info->width()/2,-200-oppo_info->height()/2);

    //增加技能栏
    QGraphicsItem *skillButtonContainer = new QGraphicsRectItem;
    skillButtonContainer->setTransform(QTransform::fromScale(0.75, 0.75), true);
    skillButtonContainer->setPos(-200, 200);
    skillButtonContainer->setZValue(65);

    QPixmap pix(":/image/image/fire.png");
    pix=pix.scaled(90,90);
    int m_width=pix.width()+1;
    GraphicsButton *btn1 = new GraphicsButton(pix, skillButtonContainer);
    GraphicsButton *btn2 = new GraphicsButton(pix, skillButtonContainer);
    GraphicsButton *btn3 = new GraphicsButton(pix, skillButtonContainer);
    GraphicsButton *btn4 = new GraphicsButton(pix, skillButtonContainer);
    btn1->setPos(0-m_width*1.5, 0);
    btn2->setPos(0-m_width/2, 0);
    btn3->setPos(m_width/2, 0);
    btn4->setPos(m_width*1.5, 0);
    addItem(skillButtonContainer);

    connect(btn1,&GraphicsButton::pressed,this,[=](){
       poke->useSkill(0,poke2);
       oppo_info->refreshHp();
    });

    //增加敌我图片
    auto item = addPixmap(pix);
    item->setPos(-200-pix.width()/2, 100);

    item = addPixmap(pix);
    item->setPos(200-pix.width()/2, -100);
}
