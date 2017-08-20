#include <QString>
#include <QDebug>
#include <QPixmap>
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
    QPixmap back(":/image/image/1b.png");
    QPixmap front(":/image/image/1f.png");
    auto item = addPixmap(back);
    item->setPos(-300-m_width/2, 100-m_width/2);
    item = addPixmap(front);
    item->setPos(200-m_width/2, -300+m_width/2);
}
