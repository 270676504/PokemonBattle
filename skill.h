#ifndef SKILL_H
#define SKILL_H

#include <QString>
#include "pokemon.h"
#include <QByteArray>
class AbstractSkill
{
public:
    enum AtkMode{
        physical,special,change
    };
    AbstractSkill(const QString& name,PokemonAttribute attribute, AtkMode mode, int power);
    virtual ~AbstractSkill();
    virtual void doAction(PokemonPtr self,PokemonPtr target)=0;
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
    enum BuffTarget{
        Self,Opponent
    };
    //主要攻击技能，提升状态可在最后一个参数追加
    NormalSkill(const QString name,PokemonAttribute attribute, AtkMode mode,int power, QVector<int> status = QVector<int>(),BuffTarget target = Self);
    //主要变化类技能，最后两个参数可设置（其实没什么软用）
    NormalSkill(const QString name,QVector<int> status,BuffTarget target = Self, PokemonAttribute attribute = PokemonAttribute::empty,AtkMode mode = AtkMode::change);
    ~NormalSkill();

    virtual void doAction(PokemonPtr self, PokemonPtr target) override;
private:
    QVector<int> m_status;    //共5个字节，代表5个属性，按照atk，def，spatk，spdef，speed排列,传字符串就行了，例如"11111"
    BuffTarget m_buff_target;
};

typedef QSharedPointer<AbstractSkill> SkillPtr;
typedef AbstractSkill::AtkMode SkillAtkMode;

#endif // SKILL_H
