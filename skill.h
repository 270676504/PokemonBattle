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
    AbstractSkill(const QString& name, AbstractSkill::AtkMode mode, int power, int hiteRate, int ppMax, int ppCurrent);
    virtual void doAction(Pokemon* self,Pokemon* object)=0;
public:
     static double damageCoefficient[20][20];
protected:
    int m_id;                                     //编号
    QString m_name;                               //技能名字
    AbstractPokemon::Attribute m_attribute;       //技能属性
    AtkMode m_atkMode;                            //攻击类型（变化类还是物理攻击还是特殊攻击）
    int m_power;                                  //技能威力
    int m_hitRate;                                //命中率 80% 记录80
    int m_ppMax;                                  //最大次数
    int m_ppCurrent;                              //剩余pp
};

class DamageSkill : public AbstractSkill{
public:
    DamageSkill(const QString name, AtkMode mode,int power,int hiteRate,int ppMax,int ppCurrent);
    virtual void doAction(Pokemon* self,Pokemon* object) override;

};

#endif // SKILL_H
