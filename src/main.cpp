#include "mainwindow.h"
#include <QApplication>
#include <stdlib.h>
#include <QSqlQuery>
#include <QSqlDatabase>
#define ATK		1
#define SPATK 	2

extern char *nature[20];

typedef enum nature
{
      empty,normal,fire,water,grass,electric,ice,bug,flying,ground,rock,fighting, psychic,ghost,poison,dark,steel,dragon,fairy
}nature_t;

typedef struct skill
{
    char name[16];			//技能名字
    nature_t nature;		//技能属性
    int id;					//编号
    int atkMode;			//攻击属性（变化类还是物理攻击还是特殊攻击）
    int power;				//技能威力
    int hitrate;			//命中率
    int ppMax;				//最大次数
}skill_t;

typedef struct learnedSkill
{
    skill_t *skill;			//skill
    int id;					//加载时链接到skill用
    int pp;					//pp值
    int state;				//状态
}learnedSkill_t;

typedef struct stature		//俗称6围
{
    int hp;					//血量
    int atk;				//物理攻击力
    int def;				//物理防御力
    int spatk;				//特殊攻击力
    int spdef;				//特殊防御力
    int speed;				//速度
}stature_t;

typedef struct pokemon
{
    char name[16];			//名字
    nature_t nature[2];		//属性
    stature_t stature;		//种族6围属性
    int id;					//口袋图鉴号码
}pkm_t;

typedef struct pokemonOwn
{
    int id;							//找图鉴的关键
    char nickName[16];				//昵称(不设置使用通用属性的昵称)
    pkm_t *pokedex;					//精灵图鉴
    learnedSkill_t learnedSkill[4];	//技能
    stature_t stature;				//6围属性
    int hpMax;						//最大hp
    int individual[6];				//个体
    int strive[6];					//努力
    int level;						//等级
    int exp;						//经验
    int character;					//性格
}pkmOwn_t;

skill_t* skilldex;

pkm_t* pokedex;

char *bag[100];

void loadPokedex(pkm_t* pokedex,int len)
{
    FILE *fp=NULL;
    fp=fopen("E:\\QTfile\\old\\PokemonBattle\\pokedex.db","rb");
    if(fp==NULL){return;}
    fread(pokedex,sizeof(pkm_t),len,fp);
    fclose(fp);
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
