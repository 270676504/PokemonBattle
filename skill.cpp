#include "skill.h"
#include <QTime>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
double AbstractSkill::damageCoefficient[20][20]=
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



//AbstractSkill::AbstractSkill(const QString &name)
//{

//}

AbstractSkill::AbstractSkill(const QString& name, PokemonAttribute attribute, AtkMode mode, int power,int PP, int accuracy)
    :m_name(name),m_attribute(attribute), m_atkMode(mode),m_accuracy(accuracy),m_power(power),m_ppMax(PP),m_ppCurrent(PP)
{
    m_isVaild = true;
}

AbstractSkill::~AbstractSkill()
{

}

void AbstractSkill::firstLearnSkill(PokemonPtr pokemon)
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
        qDebug("error : db open failed!");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT name,power,accuracy,PP,attribute,Form,buff_value,effect1,effect2,effect3,effect4,effect5 from skill where name in "
                  "(SELECT sklName from Pokemon_Skill_Learn where  sklType = 1 AND pmid = :id AND value <= :value)");
    query.bindValue(":id",pokemon->id());
    query.bindValue(":value",pokemon->level());
    query.exec();
    int i=0;
    while (query.next()){
        QString name = query.value(0).toString();
        int power = query.value(1).toInt();
        int accuracy = query.value(2).toInt();
        int PP = query.value(3).toInt();
        PokemonAttribute attribute = (PokemonAttribute)query.value(4).toInt();
        SkillAtkMode form = (SkillAtkMode)query.value(5).toInt();
        int buff_value= query.value(6).toInt();
        int count =7;
        QVector<int> effects;
        while(1)
        {
            int effect = query.value(count++).toInt();
            if(effect==0)
                break;
            effects.push_back(effect);

        }
        if(effects.isEmpty())
        {//无特效技能，攻击技能和buff技能
            SkillPtr skill =SkillPtr(new NormalSkill(name,attribute,form,power,PP,accuracy,buff_value));
            pokemon->learnSkill(skill);
        }
        else
        {//有特效的技能

        }
        i++;
        if(i>=4)
            break;
    }
    db.close();
}

SkillPtr AbstractSkill::getSkill(QString name)
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
        qDebug("errPokemonAttributeled!");
        return SkillPtr(nullptr);
    }

    QSqlQuery query;
    query.prepare("SELECT power,accuracy,PP,attribute,Form,buff_value,effPokemonAttributeect3,effect4,effect5 from skill where name = :name ");
    query.bindValue(":name",name);
    query.exec();
    while (query.next()){
        int power = query.value(0).toInt();
        int accuracy = query.value(1).toInt();
        int PP = query.value(2).toInt();
        PokemonAttribute attribute = (PokemonAttribute)query.value(3).toInt();
        SkillAtkMode form = (SkillAtkMode)query.value(4).toInt();
        int buff_value= query.value(5).toInt();
        int count =6;
        QVector<int> effects;
        while(1)
        {
            int effect = query.value(count++).toInt();
            if(effect==0)
                break;
            effects.push_back(effect);

        }
        if(effects.isEmpty())
        {//无特效技能，攻击技能和buff技能
            SkillPtr skill =SkillPtr(new NormalSkill(name,attribute,form,power,PP,accuracy,buff_value));
            return skill;
        }
        else
        {//有特效的技能

        }

    }
    db.close();
    return SkillPtr(nullptr);
}


//NormalSkill::NormalSkill(const QString name)
//    :AbstractSkill(name)
//{

//}

NormalSkill::NormalSkill(QString name, PokemonAttribute attribute, AtkMode mode, int power,int PP,int accuracy, int status)
    :AbstractSkill(name,attribute, mode, power,PP,accuracy),m_status(status)
{

}

//NormalSkill::NormalSkill(QString name, int status,int PP,int accuracy,PokemonAttribute attribute, AtkMode mode)
//    :AbstractSkill(name,attribute, mode, 0,PP,accuracy),m_status(status)
//{

//}

void NormalSkill::doAction(PokemonPtr self, PokemonPtr target)
{
    //伤害计算
    if(m_power)
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

    //状态提升,换算法
//    if(!m_status.isEmpty())
//    {
//        if(m_buff_target == Self)
//            self->changeStatus(m_status);
//        else
//            target->changeStatus(m_status);
//    }
}

NormalSkill::~NormalSkill()
{

}




