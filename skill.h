#ifndef SKILL_H
#define SKILL_H

#include <QString>
#include "pokemon.h"
#include <QByteArray>
#define POKEMON_DB_PATH "D:\\pokedex2.db"
class AbstractSkill
{
public:
    enum AtkMode{
        physical = 0,special = 1,change = 2
    };
//    AbstractSkill(const QString& name);
    AbstractSkill(const QString& name,PokemonAttribute attribute, AtkMode mode, int power,int PP,int accuracy = 100);
    virtual ~AbstractSkill();
    virtual void doAction(PokemonPtr self,PokemonPtr target)=0;
    bool isVaild(){return m_isVaild;}
public:
    static double damageCoefficient[20][20];    //伤害系数
    static void firstLearnSkill(PokemonPtr pokemon);
    static SkillPtr getSkill(QString name);
protected:
    QString m_name;                             //技能名字
    PokemonAttribute m_attribute;               //技能属性
    AtkMode m_atkMode;                          //攻击类型（变化类还是物理攻击还是特殊攻击）
    int m_accuracy = 100;                        //命中率 80% 记录80
    int m_power;                                //技能威力
    int m_ppMax;                                //最大次数
    int m_ppCurrent;                            //剩余pp
    bool m_isVaild = false;
};

class NormalSkill : public AbstractSkill{
public:
//    NormalSkill(QString name);
    //主要攻击技能，提升状态可在最后一个参数追加
    NormalSkill(QString name,PokemonAttribute attribute, AtkMode mode,int power,int PP,int accuracy = 100, int status = 0);
    ~NormalSkill();
    virtual void doAction(PokemonPtr self, PokemonPtr target) override;
private:
    int m_status;    //共5个int，代表5个属性，按照atk，def，spatk，spdef，speed提升等级
};

typedef QSharedPointer<AbstractSkill> SkillPtr;
typedef AbstractSkill::AtkMode SkillAtkMode;

#endif // SKILL_H
