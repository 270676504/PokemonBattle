#ifndef SKILL_H
#define SKILL_H

#include <QString>
#include "pokemon.h"
class AbstractSkill
{
public:
    enum AtkMode{
        physical,special,change
    };
    AbstractSkill();
    virtual void doAction(Pokemon* self,Pokemon* object)=0;
public:
     static double damageCoefficient[20][20];
protected:
    int id;                                     //编号
    QString name;                               //技能名字
    AbstractPokemon::Attribute attribute;       //技能属性
    AtkMode atkMode;                            //攻击类型（变化类还是物理攻击还是特殊攻击）
    int power;                                  //技能威力
    int hitRate;                                //命中率 80% 记录80
    int ppMax;                                  //最大次数
    int ppCurrent;                              //剩余pp
};

class DamageSkill : public AbstractSkill{
    virtual void doAction(Pokemon* self,Pokemon* object);

};

#endif // SKILL_H
