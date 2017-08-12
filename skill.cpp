#include "skill.h"
#include <QTime>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
double Skill::damageCoefficient[20][20]=
            //无, 普, 火,  水, 草, 电, 冰, 虫,  飞, 地, 岩, 格,  超, 鬼, 毒,  恶, 钢, 龙, 妖,无
            {{0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18,0}, //无
             {1,  1,  1,  1,  1,  1,  1,  1,  1,  1,0.5,  1,  1,  0,  1,  1,0.5,  1,  1,0}, //普
             {2,  1,0.5,0.5,  2,  1,  2,  2,  1,  1,0.5,  1,  1,  1,  1,  1,  2,0.5,  1,0},	//火
             {3,  1,  2,0.5,0.5,  1,  1,  1,  1,  2,  2,  1,  1,  1,  1,  1,  1,0.5,  1,0},	//水
             {4,  1,0.5,  2,0.5,  1,  1,0.5,0.5,  2,  2,  1,  1,  1,0.5,  1,0.5,0.5,  1,0}, //草
             {5,  1,  1,  2,0.5,0.5,  1,  1,  2,  0,  1,  1,  1,  1,  1,  1,  1,0.5,  1,0}, //电
             {6,  1,0.5,0.5,  2,  1,0.5,  1,  2,  2,  1,  1,  1,  1,  1,  1,0.5,  2,  1,0}, //冰
             {7,  1,0.5,  1,  2,  1,  1,  1,0.5,  1,  1,0.5,  2,0.5,0.5,  2,0.5,  1,0.5,0}, //虫
             {8,  1,  1,  1,  2,0.5,  1,  2,  1,  1,0.5,  2,  1,  1,  1,  1,0.5,  1,  1,0}, //飞
             {9,  1,  2,  1,0.5,  2,  1,0.5,  0,  1,  2,  1,  1,  1,  2,  1,  2,  1,  1,0}, //地
            {10,  1,  2,  1,  1,  1,  2,  2,  2,0.5,  1,0.5,  1,  1,  1,  1,0.5,  1,  1,0}, //岩
            {11,  2,  1,  1,  1,  1,  1,0.5,0.5,  1,  2,  1,  1,  0,0.5,  1,  2,  1,  1,0}, //格
            {12,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,0.5,  1,  2,  0,0.5,  1,  1,0}, //超
            {13,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  1,0.5,  1,  1,  1,0}, //鬼
            {14,  1,  1,  1,  2,  1,  1,  1,  1,0.5,0.5,  1,  1,0.5,0.5,  1,  0,  1,  2,0}, //毒
            {15,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,0.5,  2,  2,  1,0.5,  1,  1,0.5,0}, //恶
            {16,  1,0.5,0.5,  1,0.5,  2,  1,  1,  1,  2,  1,  1,  1,  1,  1,0.5,  1,  2,0}, //钢
            {17,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  0,0}, //龙
            {18,  1,0.5,  1,  1,  1,  1,  1,  1,  1,  1,  2,  1,  1,0.5,  2,0.5,  2,  1,0}, //妖
             {0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,0}};


Skill::Skill(const QString &name)
    :m_name(name)
{
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection")){
        db = QSqlDatabase::database("qt_sql_default_connection");
    }else{
        db = QSqlDatabase::addDatabase("QSQLITE");
    }
    db.setDatabaseName(QString(POKEMON_DB_PATH));

    if(!db.open())
    {
        qDebug("error:db open failed!(_Skill::Skill(const QString &name)_)");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT power,accuracy,PP,attribute,Form,buff_value,effect1,effect2,effect3,effect4,effect5 from skill where name = :name ");
    query.bindValue(":name",name);
    query.exec();
    if (query.next()){
        m_power = query.value(0).toInt();
        m_accuracy = query.value(1).toInt();
        m_ppMax= query.value(2).toInt();
        m_ppCurrent=m_ppMax;
        m_attribute = (PokemonAttribute)query.value(3).toInt();
        m_atkMode = (SkillAtkMode)query.value(4).toInt();
        m_status= query.value(5).toInt();
        qDebug()<<m_name;
        qDebug()<<m_status;
        int count =6;
        while(1)
        {
            int effect = query.value(count++).toInt();
            if(effect==0)
                break;
            effects.push_back(effect);
        }
        m_isVaild = true;
    }

    db.close();
}

Skill::~Skill()
{

}

void Skill::doAction(PokemonPtr self, PokemonPtr target)
{
    //伤害计算
    if(m_power)
    {
      makeDamage(self,target);
    }
    if(m_status)
    {
        statusChange(self,target);
    }


}

void Skill::makeDamage(PokemonPtr self, PokemonPtr target)
{
    double ret = 1;
    double power_coefficient = 1;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    //伤害值＝[(攻击方的LV×0.4＋2)×技巧威力×攻击方的攻击（或特攻）能力值÷防御方的防御（或特防）能力值÷50＋2]×各类修正×(217～255之间)÷255
    switch (m_atkMode) {
    case physical:
        ret = (m_power * ((self->level() * 0.4 + 2) * self->currentAtk() / target->currentDef()) / 50.0 + 2)
                * (qrand() % 39+217)/255;                                                 //伤害浮动（217~255）/255
        break;
    case special:
        ret = (m_power * ((self->level() * 0.4 + 2) * self->currentSpatk() / target->currentSpdef()) / 50.0 + 2)
                * (qrand() % 39 + 217) / 255;
        break;
    default:
        break;
    }
    for(auto attribute : target->attribute())
    {
         power_coefficient*=damageCoefficient[m_attribute][attribute];
    }
    for(auto attribute : self->attribute())
    {
        if(attribute==m_attribute)
        {
             power_coefficient *= 1.5;
             break;
        }
    }
    ret *= power_coefficient;
    target->hpReduce((int)ret);
}

void Skill::statusChange(PokemonPtr self, PokemonPtr target)
{
    //状态提升,换算法
    int back = m_status;
    for(int i = 0; back != 0 ;i++)
    {
        int judge = back % 16;
        back = back / 16 ;
        if(!judge)
        {
            continue;
        }

        PokemonStatus status = PokemonStatus::NONE;
        switch (i) {
        case 0:
            status =PokemonStatus::DODGE;
            break;
        case 1:
            status =PokemonStatus::ACCURACY;
            break;
        case 2:
            status =PokemonStatus::SPEED;
            break;
        case 3:
            status =PokemonStatus::SPDEF;
            break;
        case 4:
            status =PokemonStatus::SPATK;
            break;
        case 5:
            status =PokemonStatus::DEF;
            break;
        case 6:
            status =PokemonStatus::ATK;
            break;
        default:
            break;
        }

        PokemonPtr buffTarget = self;
        int buffValue = 0;
        switch (judge) {
        case 1:
            buffValue = 1;
            break;
        case 2:
            buffValue = 2;
            break;
        case 3:
            buffValue = 3;
            break;
        case 5:
            buffValue = -1;
            break;
        case 6:
            buffValue = -2;
            break;
        case 7:
            buffValue = -3;
            break;
        case 9:
            buffTarget = target;
            buffValue = 1;
            break;
        case 10:
            buffTarget = target;
            buffValue = 2;
            break;
        case 11:
            buffTarget = target;
            buffValue = 3;
            break;
        case 13:
            buffTarget = target;
            buffValue = -1;
            break;
        case 14:
            buffTarget = target;
            buffValue = -2;
            break;
        case 15:
            buffTarget = target;
            buffValue = -3;
            break;
        default:
            break;
        }

        buffTarget->changeStatus(buffValue,status);
    }
}

void Skill::firstLearnSkill(PokemonPtr pokemon)
{
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection")){
        db = QSqlDatabase::database("qt_sql_default_connection");
    }else{
        db = QSqlDatabase::addDatabase("QSQLITE");
    }
    db.setDatabaseName(QString(POKEMON_DB_PATH));

    if(!db.open())
    {
        qDebug("error : db open failed! _Skill::firstLearnSkill(PokemonPtr pokemon)_");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT sklName from Pokemon_Skill_Learn where  sklType = 1 AND pmid = :id AND value <= :value");
    query.bindValue(":id",pokemon->id());
    query.bindValue(":value",pokemon->level());
    query.exec();
    QStringList nameList;
    while (query.next()){
        QString name = query.value(0).toString();
        nameList << name;
    }
    db.close();

    for(auto name : nameList)
    {
        SkillPtr skill =SkillPtr(new Skill(name));
        if(skill->isVaild() && !pokemon->learnSkill(skill))
            break;
    }
}

