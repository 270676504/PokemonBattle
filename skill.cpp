#include "skill.h"
#include <QTime>
#include <QDebug>

double AbstractSkill::damageCoefficient[20][20]=
            //无, 普, 火,  水, 草, 电, 冰, 虫,  飞, 地, 岩, 格,  超, 鬼, 毒,  恶, 钢, 龙, 妖,无
            {{0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18,0}, //无
             {1,  1,  1,  1,  1,  1,  1,  1,  1,  1,0.5,  1,  1,  0,  1,  1,0.5,  1,  1,0}, //普
             {2,  1,0.5,0.5,  2,  1,  2,  2,  1,  1,0.5,  1,  1,  1,  1,  1,  2,0.5,  1,0},	//火
             {3,  1,  2,0.5,0.5,  1,  1,  1,  1,  2,  2,  1,  1,  1,  1,  1,  1,0.5,  1,0},	//水
             {4,  1,0.5,  2,0.5,  1,  1,0.5,0.5,  2,  2,  1,  1,  1,0.5,  1,0.5,0.5,  1,0}, //草
             {5,  1,  1,  2,0.5,0.5,  1,  1,  2,  0,  1,  1,  1,  1,  1,  1,  1,0.5,  1,0}, //电
             {6,  1,0.5,0.5,  2,  1,0.5,  1,  2,  2,  1,  1,  1,  1,  1,  1,0.5,  2,  1,0}, //冰
             {7,  1,0.5,  1,  2,  1,  1,  1,0.5,  1,  1,0.5,  2,0.5,0.5,  2,0.5,  1,0.5,0}, //虫
             {8,  1,  1,  1,  2,0.5,  1,  2,  1,  1,0.5,  2,  1,  1,  1,  1,0.5,  1,  1,0}, //飞
             {9,  1,  2,  1,0.5,  2,  1,0.5,  0,  1,  2,  1,  1,  1,  2,  1,  2,  1,  1,0}, //地
            {10,  1,  2,  1,  1,  1,  2,  2,  2,0.5,  1,0.5,  1,  1,  1,  1,0.5,  1,  1,0}, //岩
            {11,  2,  1,  1,  1,  1,  1,0.5,0.5,  1,  2,  1,  1,  0,0.5,  1,  2,  1,  1,0}, //格
            {12,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,0.5,  1,  2,  0,0.5,  1,  1,0}, //超
            {13,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  1,0.5,  1,  1,  1,0}, //鬼
            {14,  1,  1,  1,  2,  1,  1,  1,  1,0.5,0.5,  1,  1,0.5,0.5,  1,  0,  1,  2,0}, //毒
            {15,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,0.5,  2,  2,  1,0.5,  1,  1,0.5,0}, //恶
            {16,  1,0.5,0.5,  1,0.5,  2,  1,  1,  1,  2,  1,  1,  1,  1,  1,0.5,  1,  2,0}, //钢
            {17,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  0,0}, //龙
            {18,  1,0.5,  1,  1,  1,  1,  1,  1,  1,  1,  2,  1,  1,0.5,  2,0.5,  2,  1,0}, //妖
             {0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,0}};



AbstractSkill::AbstractSkill(const QString& name,AbstractPokemon::Attribute attribute, AbstractSkill::AtkMode mode, int power)
    :m_name(name),m_attribute(attribute), m_atkMode(mode),m_power(power)
{

}

AbstractSkill::~AbstractSkill()
{

}


DamageSkill::DamageSkill(const QString name,AbstractPokemon::Attribute attribute, AbstractSkill::AtkMode mode, int power)
    :AbstractSkill(name,attribute, mode, power)
{

}

void DamageSkill::doAction(PokemonPtr self, PokemonPtr object)
{
    double ret=1;
    double coefficient=1;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    //伤害值＝[(攻击方的LV×0.4＋2)×技巧威力×攻击方的攻击（或特攻）能力值÷防御方的防御（或特防）能力值÷50＋2]×各类修正×(217～255之间)÷255
    switch (m_atkMode) {
    case physical:
        ret=((self->level()*0.4+2)*m_power*self->currentStatus().atk/object->currentStatus().def/50+2)*(qrand()%39+217)/255;
        break;
    case special:
        ret=((self->level()*0.4+2)*m_power*self->currentStatus().spatk/object->currentStatus().spdef/50+2)*(qrand()%39+217)/255;
        break;
    default:
        break;
    }
    for(auto attribute : object->attribute())
    {
         coefficient*=damageCoefficient[m_attribute][attribute];
    }
    for(auto attribute : self->attribute())
    {
        if(attribute==m_attribute)
        {
             coefficient*=1.5;
             break;
        }
    }

    ret*=coefficient;
    object->hpReduce((int)ret);
}

DamageSkill::~DamageSkill()
{

}

