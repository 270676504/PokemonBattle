#ifndef SKILL_H
#define SKILL_H

#include <QString>
#include "pokemon.h"
#include <QByteArray>
#define POKEMON_DB_PATH "D:\\pokedex2.db"
class Skill
{
public:
    enum AtkMode{
        physical = 0,special = 1,change = 2
    };
    Skill(const QString& name);
    ~Skill();
    void doAction(PokemonPtr self,PokemonPtr target);
    bool isVaild(){return m_isVaild;}
    void makeDamage(PokemonPtr self,PokemonPtr target);
    void statusChange(PokemonPtr self,PokemonPtr target);
    void statusChange(PokemonPtr self, PokemonPtr target, int value);
public: //static
    static double damageCoefficient[20][20];    //伤害系数
    static void firstLearnSkill(PokemonPtr pokemon);
private:
    QString m_name;                             //技能名字
    PokemonAttribute m_attribute;               //技能属性
    AtkMode m_atkMode;                          //攻击类型（变化类还是物理攻击还是特殊攻击）
    int m_accuracy = 100;                        //命中率 80% 记录80
    int m_power;                                //技能威力
    int m_ppMax;                                //最大次数
    int m_ppCurrent;                            //剩余pp
    bool m_isVaild = false;

    //m_status 详解：第一个字段1代表对方 第二个字段1代表降低 第三第四个字段代表升高或者降低的值
    //                          攻击      防御    特攻    特防    速度      命中    回避
    //比如：叫声 降低对方1级攻击    1101    0000     0000   0000    0000    0000    0000 == 218103808;
    //  16进制表示               D000000
    //转成16进制属性详解 123自己提升123级，4没效果，567自己降低123级，8没效果，9AB对方提升123级，C没效果，DEF对方降低123级
    int m_status;    //共7个字段，代表5个属性，按照atk，def，spatk，spdef，speed提升等级,加上命中和回避
    QVector<int> effects;
};




typedef QSharedPointer<Skill> SkillPtr;
typedef Skill::AtkMode SkillAtkMode;

#endif // SKILL_H
