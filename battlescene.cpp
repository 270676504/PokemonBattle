#include <QString>
#include <QDebug>
#include <QPixmap>
#include <QLabel>
#include <QMovie>
#include <QGraphicsProxyWidget>
#include "skill.h"
#include "maininfo.h"
#include "skillbutton.h"
#include "battlescene.h"


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

    int m_width=95;
    int startPoint = 0-m_width*1.5;
    auto skills = m_pokemon->skills();
    for(auto i=0;i<skills.size();i++)
    {
         SkillButton *skillButton = new SkillButton(skills[i],skillButtonContainer);
         skillButton->setPos(startPoint, 0);
         startPoint+=m_width;
         connect(skillButton,&SkillButton::pressed,this,[=](){
            m_pokemon->useSkill(i,oppo_pokemon);
            oppo_info->refreshHp();
         });
    }
    addItem(skillButtonContainer);

    //增加敌我图片
    QLabel *gif_anim = new QLabel();
    QString path = getGifPath(Face::Back,m_pokemon->id());
    QMovie *movie = new QMovie(path);
    movie->setScaledSize(QSize(200,200));
    gif_anim->setMovie(movie);
    movie->start();
    QGraphicsProxyWidget *proxy = addWidget(gif_anim);
    proxy->setPos(-300-m_width/2, 100-m_width/2);

    gif_anim = new QLabel();
    path = getGifPath(Face::Front,oppo_pokemon->id());
    movie = new QMovie(path);
    movie->setScaledSize(QSize(200,200));
    gif_anim->setMovie(movie);
    movie->start();
    proxy = addWidget(gif_anim);
    proxy->setPos(200-m_width/2, -300+m_width/2);
}

QString BattleScene::getGifPath(BattleScene::Face face, int id)
{
    QString path = "D:\\Pokemon_image_source\\%1\\gen.%2\\%3.gif";
    QString qFace;
    QString gen;
    QString qID;

    if(face == Face::Back){
        qFace = "back";
    }else{
        qFace = "front";
    }

    if(id<152){
        gen = "1";
    }else if(id<252){
        gen = "2";
    }else if(id<387){
        gen = "3";
    }else if(id<494){
        gen = "4";
    }else{
        gen = "5";
    }

    if(id < 10){
        qID = "00"+ QString::number(id);
    }else if(id<100){
         qID = "0"+ QString::number(id);
    }else{
        qID = QString::number(id);
    }

    return path.arg(qFace).arg(gen).arg(qID);
}
