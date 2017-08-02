#include "battlescene.h"
#include "maininfo.h"
#include <QGraphicsProxyWidget>
#include "graphicsbutton.h"
#include <QPixmap>
#include <QDebug>
BattleScene::BattleScene(QObject *parent)
    :QGraphicsScene(parent)
{
    Pokemon* poke=new Pokemon(3);
    m_info=new MainInfo();
    oppo_info=new MainInfo();
    m_info->setInfo(poke);
    oppo_info->setInfo(poke);
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

    connect(btn1,&GraphicsButton::pressed,this,[&](){
        qDebug()<<"clicked";
    });

    //增加敌我图片
    auto item = addPixmap(pix);
    item->setPos(-200-pix.width()/2, 100);

    item = addPixmap(pix);
    item->setPos(200-pix.width()/2, -100);
}
