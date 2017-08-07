#include "pokemon.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDir>
#include <qdebug>
#include <QTime>
#include "skill.h"
#define POWER_UP_MAX_COUNT 5
const QVector<QString> AbstractPokemon::word_attribute={u8"无",       //0
                                                   u8"普",       //1
                                                   u8"火",       //2
                                                   u8"水",       //3
                                                   u8"草",       //4
                                                   u8"电",       //5
                                                   u8"冰",       //6
                                                   u8"虫",       //7
                                                   u8"飞",       //8
                                                   u8"地",       //9
                                                   u8"岩",       //10
                                                   u8"格",       //11
                                                   u8"超",       //12
                                                   u8"鬼",       //13
                                                   u8"毒",       //14
                                                   u8"恶",       //15
                                                   u8"钢",       //16
                                                   u8"龙",       //17
                                                   u8"妖"};      //18

AbstractPokemon::AbstractPokemon(int id)
    :m_id(id)
{
    QString dbFile("D:\\pokedex2.db");
    QSqlDatabase db;

    if(QSqlDatabase::contains("qt_sql_default_connection")){
        db = QSqlDatabase::database("qt_sql_default_connection");
    }else{
        db = QSqlDatabase::addDatabase("QSQLITE");
    }
    db.setDatabaseName(dbFile);

    if(db.open())
    {
        QSqlQuery query;
        query.prepare("SELECT pmid,name,hp,atk,def,spatk,spdef,speed,type1,type2 from Pokemon where pmid=:id");
        query.bindValue(":id",id);
        query.exec();
        while (query.next()){                       //存在记录
            m_name= query.value(1).toString();
            m_racialValue.hp= query.value(2).toInt();
            m_racialValue.atk= query.value(3).toInt();
            m_racialValue.def= query.value(4).toInt();
            m_racialValue.spatk= query.value(5).toInt();
            m_racialValue.spdef= query.value(6).toInt();
            m_racialValue.speed= query.value(7).toInt();
            m_attribute.push_back((AbstractPokemon::Attribute)query.value(8).toInt());
            int secondary_attribute =query.value(9).toInt();
            if(secondary_attribute){
                m_attribute.push_back((AbstractPokemon::Attribute)secondary_attribute);
            }
        }
    }
    db.close();
}

Pokemon::Pokemon(int id,int level)
    :AbstractPokemon(id),m_effortValue({0,0,0,0,0,0}),m_level(level)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    m_individualValue.hp = qrand()%32;
    m_individualValue.atk = qrand()%32;
    m_individualValue.def = qrand()%32;
    m_individualValue.spatk = qrand()%32;
    m_individualValue.spdef = qrand()%32;
    m_individualValue.speed = qrand()%32;

    m_currentHp=( m_racialValue.hp*2+ m_individualValue.hp)*m_level/100+10+m_level;
    m_hpMax=(m_racialValue.hp*2+m_individualValue.hp)*m_level/100+10+m_level;
}

Pokemon::~Pokemon()
{

}

void Pokemon::hpReduce(int value)
{
    m_currentHp -= value;
    if(m_currentHp < 0)
    {
        m_currentHp = 0;
    }
}

void Pokemon::learnSkill(SkillPtr skill)
{
    if(learnedSkill.size() < 4)
        learnedSkill.push_back(skill); //先偷个懒，后面还有
}

void Pokemon::useSkill(int index, PokemonPtr target)
{
    qDebug()<<learnedSkill.size();
    if(index >= learnedSkill.size())
        return;
    const SkillPtr& skill = learnedSkill.at(index);
    skill->doAction(sharedFromThis(),target);
}

void Pokemon::resetStatus()
{
    m_atk_level = 2;                //当前属性等级（2级为100%）
    m_def_level = 2;
    m_spatk_level= 2;
    m_spdef_level = 2;
    m_speed_level= 2;
}

void Pokemon::changeStatus(QVector<int> status)
{
    if(status.size()<5)
        return;
    qDebug()<<currentAtk()<<currentDef()<<currentSpatk()<<currentSpdef()<<currentSpeed();
    changeStatus(m_atk_level,status.at(0));
    changeStatus(m_def_level,status.at(1));
    changeStatus(m_spatk_level,status.at(2));
    changeStatus(m_spdef_level,status.at(3));
    changeStatus(m_speed_level,status.at(4));

    qDebug()<<currentAtk()<<currentDef()<<currentSpatk()<<currentSpdef()<<currentSpeed();
}

void Pokemon::changeStatus(int& valueToChange,int status)
{
    if(status == 0)
        return;

    valueToChange += status;

    if(valueToChange > 6)
        valueToChange = 6;
    else if(valueToChange < -6)
        valueToChange = -6;
}

double Pokemon::statusCoefficient(int statusLevel)
{
    switch(statusLevel)
    {
    case -6:
        return 2.0 / 8;     //  -6级25%
    case -5:
        return 2.0 / 7;
    case -4:
        return 2.0 / 6;
    case -3:
        return 2.0 / 5;
    case -2:
        return 2.0 / 4;
    case -1:
        return 2.0 / 3;
    case 0:
        return 2.0 / 2;
    case 1:
        return 3.0 / 2;
    case 2:
        return 4.0 / 2;
    case 3:
        return 5.0 / 2;
    case 4:
        return 6.0 / 2;
    case 5:
        return 7.0 / 2;
    case 6:
        return 8.0 / 2;     //  6级400%
    default:
        return 0;
    }
    return 0;
}
