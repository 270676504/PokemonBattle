#ifndef POKEMON_H
#define POKEMON_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QEnableSharedFromThis>
#include <QByteArray>
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
    enum PowerUpStatus{
        NONE = 0, //说明：如果想提升2档atk，只需要传入ATK*2就行了
        ATK = 1 << 0,
        DEF = 1 << 5,
        SPATK = 1 << 10,
        SPDEF = 1 << 15,
        SPEED = 1 << 20,
        DEBUFF = 1<< 31, //if this value set 1 ,it means debuff
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

class Pokemon :public AbstractPokemon , public QEnableSharedFromThis<Pokemon> {
public:
    explicit Pokemon(int id, int level = 5);
    ~Pokemon();
    QString nickName(){return m_nickName;}
    Stature individualValue(){return m_individualValue;}
    Stature effortValue(){return m_effortValue;}

    int currentHp(){return m_currentHp;}
    int currentAtk(){return ((m_racialValue.atk*2+m_individualValue.atk)*m_level/100+5) * statusCoefficient(m_atk_level);}
    int currentDef(){return ((m_racialValue.def*2+m_individualValue.def)*m_level/100+5) * statusCoefficient(m_def_level);}
    int currentSpatk(){return ((m_racialValue.spatk*2+m_individualValue.spatk)*m_level/100+5) * statusCoefficient(m_spatk_level);}
    int currentSpdef(){return ((m_racialValue.spdef*2+m_individualValue.spdef)*m_level/100+5) * statusCoefficient(m_spdef_level);}
    int currentSpeed(){return ((m_racialValue.speed*2+m_individualValue.speed)*m_level/100+5) * statusCoefficient(m_speed_level);}
    int level(){return m_level;}
    int exp(){return m_exp;}
    int hpMax(){return m_hpMax;}

    void hpReduce(int value);
    void learnSkill(SkillPtr skill);
    void useSkill(int index, PokemonPtr target);
    void resetStatus();
    void changeStatus(QVector<int> status);

protected:
    void changeStatus(int& valueToChange, int status);
    double statusCoefficient(int statusLevel);
private:
    QString m_nickName;             //昵称
    Stature m_individualValue;      //个体值
    Stature m_effortValue;          //努力值
    int m_currentHp;
    int m_atk_level = 0;                //当前属性等级（2级为100%）
    int m_def_level = 0;
    int m_spatk_level= 0;
    int m_spdef_level = 0;
    int m_speed_level= 0;
    //Stature m_currentStatus;
    int m_level;					//等级
    int m_exp;                      //经验
    int m_hpMax;
    int m_character;				//性格
    QVector<SkillPtr> learnedSkill;
};

typedef AbstractPokemon::Attribute PokemonAttribute;
typedef AbstractPokemon::PowerUpStatus PokemonStatus;
#endif // POKEMON_H
