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

    AbstractSkill(const QString& name,PokemonAttribute attribute, AtkMode mode, int power);
    virtual ~AbstractSkill();
    int m_hitRate = 100;                          //命中率 80% 记录80
    virtual void doAction(PokemonPtr self,PokemonPtr object)=0;
public:
     static double damageCoefficient[20][20];
protected:
    int m_id;                                     //编号
    int m_ppCurrent;                              //剩余pp
    QString m_name;                               //技能名字
    AbstractPokemon::Attribute m_attribute;       //技能属性
    AtkMode m_atkMode;                            //攻击类型（变化类还是物理攻击还是特殊攻击）
    int m_power;                                  //技能威力
    int m_ppMax;                                  //最大次数
};

class DamageSkill : public AbstractSkill{
public:
    DamageSkill(const QString name,AbstractPokemon::Attribute attribute, AtkMode mode,int power);
    ~DamageSkill();
    virtual void doAction(PokemonPtr self, PokemonPtr object) override;
};

typedef QSharedPointer<AbstractSkill> SkillPtr;
typedef AbstractSkill::AtkMode SkillAtkMode;

#endif // SKILL_H
