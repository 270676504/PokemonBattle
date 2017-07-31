#ifndef SKILL_H
#define SKILL_H

#include <QString>

class AbstractSkill
{
public:
    enum AtkMode{
        physical,special,change
    };
    AbstractSkill();
private:
    QString name;			//技能名字
    //nature_t nature;		//技能属性
    int id;					//编号
    AtkMode atkMode;		//攻击属性（变化类还是物理攻击还是特殊攻击）
    int power;				//技能威力
    int hitRate;			//命中率 80% 记录80
    int ppMax;				//最大次数
};

class Skill :public AbstractSkill
{
private:
    int ppCurrent;
};

#endif // SKILL_H
