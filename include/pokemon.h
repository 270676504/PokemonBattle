#ifndef POKEMON_H
#define POKEMON_H

#include <QObject>
#include <QString>

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
    enum Nature{
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
    explicit AbstractPokemon(QString name,Stature racialValue,Nature nature1,Nature nature2 = empty);
private:
    QString name;           //名字
    Nature nature[2];		//属性
    Stature racialValue;	//种族值
    int id;					//口袋图鉴号码
};

class Pokemon :public AbstractPokemon{
public:
    explicit Pokemon(QString name,Stature racialValue,Nature nature1,Nature nature2 = empty);
private:
    QString nickName;           //昵称
    Stature individualValue;	//个体值
    Stature effortValue;        //努力值
    Stature currentValue;       //当前属性
    int level;					//等级
    int exp;					//经验
    int character;				//性格
};


#endif // POKEMON_H
