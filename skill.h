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
    virtual void doAction(PokemonPtr self,PokemonPtr target,PokemonPtr buffTarget = PokemonPtr(nullptr))=0;
public:
    static double damageCoefficient[20][20];    //伤害系数
protected:
    int m_id;                                   //编号
    int m_ppCurrent;                            //剩余pp
    QString m_name;                             //技能名字
    PokemonAttribute m_attribute;               //技能属性
    AtkMode m_atkMode;                          //攻击类型（变化类还是物理攻击还是特殊攻击）
    int m_hitRate = 100;                        //命中率 80% 记录80
    int m_power;                                //技能威力
    int m_ppMax;                                //最大次数
};

class NormalSkill : public AbstractSkill{
public:
    enum PowerUpStatus{
        NONE = 0, //说明：如果想提升2档atk，只需要传入ATK*2就行了
        ATK = 1 << 0,
        DEF = 1 << 5,
        SPATK = 1 << 10,
        SPDEF = 1 << 15,
        SPEED = 1 << 20,
        DEBUFF = 1<< 31, //if this value set 1 ,it means debuff
    };
    //主要攻击技能，提升状态可在最后一个参数追加
    NormalSkill(const QString name,PokemonAttribute attribute, AtkMode mode,int power, PowerUpStatus status = NONE);
    //主要变化类技能，最后两个参数可设置（其实没什么软用）
    NormalSkill(const QString name,PowerUpStatus status,PokemonAttribute attribute=PokemonAttribute::empty,AtkMode mode=AtkMode::change);
    ~NormalSkill();
    //如果是
    virtual void doAction(PokemonPtr self, PokemonPtr target,PokemonPtr buffTarget = PokemonPtr(nullptr)) override;
private:
    PowerUpStatus m_status;
};

typedef QSharedPointer<AbstractSkill> SkillPtr;
typedef AbstractSkill::AtkMode SkillAtkMode;

#endif // SKILL_H
