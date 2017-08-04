#ifndef POKEMON_H
#define POKEMON_H

#include <QObject>
#include <QString>
#include <QVector>

class AbstractSkill;
typedef QSharedPointer<AbstractSkill> SkillPtr;

class Pokemon;
typedef QSharedPointer<Pokemon> PokemonPtr;
class AbstractPokemon{
public:
    struct Stature              //俗称6围
    {
        int hp;					//血量
        int atk;				//物理攻击力
        int def;				//物理防御力
        int spatk;				//特殊攻击力
        int spdef;				//特殊防御力
        int speed;				//速度
    };
    enum Attribute{
        empty=0,        //无
        normal,         //普
        fire,           //火
        water,          //水
        grass,          //草
        electric,       //电
        ice,            //冰
        bug,            //虫
        flying,         //飞
        ground,         //地
        rock,           //岩
        fighting,       //斗
        psychic,        //超
        ghost,          //鬼
        poison,         //毒
        dark,           //恶
        steel,          //钢
        dragon,         //龙
        fairy           //妖
    };

    static const QVector<QString> word_attribute;
    explicit AbstractPokemon(int m_id);
    QString name(){return m_name;}
    Stature racialValue(){return m_racialValue;}
    QVector<AbstractPokemon::Attribute> attribute(){return m_attribute;}
    int id(){return m_id;}
protected:
    int m_id;                                           //口袋图鉴号码
    QString m_name;                                     //名字
    Stature m_racialValue;                              //种族值
    QVector<AbstractPokemon::Attribute> m_attribute;    //属性
};

class Pokemon :public AbstractPokemon{
public:
    explicit Pokemon(int id, int level = 5);
    QString nickName(){return m_nickName;}
    Stature individualValue(){return m_individualValue;}
    Stature effortValue(){return m_effortValue;}
    Stature currentStatus(){return m_currentStatus;}
    int level(){return m_level;}
    int exp(){return m_exp;}
    int hpMax(){return m_hpMax;}
    void hpReduce(int value);
    void learnSkill(SkillPtr skill);
    void useSkill(int index, PokemonPtr target);
    void reCalculateCurrentState();
protected:

private:
    QString m_nickName;             //昵称
    Stature m_individualValue;      //个体值
    Stature m_effortValue;          //努力值
    Stature m_currentStatus;        //当前属性
    int m_level;					//等级
    int m_exp;                      //经验
    int m_hpMax;
    int m_character;				//性格
    QVector<SkillPtr> learnedSkill;
};

typedef AbstractPokemon::Attribute PokemonAttribute;
#endif // POKEMON_H
