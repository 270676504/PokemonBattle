﻿#include "pokemon.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDir>
#include <qdebug>
#include <QTime>
#include "skill.h"
#define POWER_UP_MAX_COUNT 5

const QVector<QString> AbstractPokemon::attributeArray={u8"无",       //0
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
    query.prepare("SELECT name,hp,atk,def,spatk,spdef,speed,Attribute1,Attribute2 from Pokemon where pmid=:id");
    query.bindValue(":id",id);
    query.exec();
    while (query.next()){                       //存在记录
        m_name= query.value(0).toString();
        m_racialValue.hp= query.value(1).toInt();
        m_racialValue.atk= query.value(2).toInt();
        m_racialValue.def= query.value(3).toInt();
        m_racialValue.spatk= query.value(4).toInt();
        m_racialValue.spdef= query.value(5).toInt();
        m_racialValue.speed= query.value(6).toInt();
        m_attribute.push_back((AbstractPokemon::Attribute)query.value(7).toInt());
        int secondary_attribute =query.value(8).toInt();
        if(secondary_attribute){
            m_attribute.push_back((AbstractPokemon::Attribute)secondary_attribute);
        }
    }
    query.prepare("SELECT sklType,sklName,Value from Pokemon_Skill_Learn where pmid=:id");
    query.bindValue(":id",id);
    query.exec();

    while (query.next()){
        int type = query.value(0).toInt();
        QString name = query.value(1).toString();
        int num = query.value(2).toInt();
        switch(type)
        {
        case 1:
            if(num == -1){
                not_evolved_skill.push_back(name);
            }else if(num == 0){
                basic_skill.push_back(name);
            }else{
                lv_skill.insert(num,name);
            }
            break;
        case 2:
            TM_skill.push_back(num);
            break;
        case 3:
            HM_skill.push_back(num);
            break;
        case 4:
            teach_skill.push_back(name);
            break;
        case 5:
            inheritance_skill.push_back(name);
            break;
        default:
            qDebug("error:wrong skillType");
            break;
        }
    }
    db.close();
}

Pokemon::Pokemon(int id,int level)
    :AbstractPokemon(id),m_level(level)
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

bool Pokemon::learnSkill(SkillPtr skill)
{
    if(learnedSkill.size() >= 4)
        return false;

    learnedSkill.push_back(skill); //先偷个懒，后面还有
    return true;
}

void Pokemon::useSkill(int index, PokemonPtr target)
{
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

void Pokemon::changeStatus(int value, PowerUpStatus stauts)
{
    qDebug()<<"buff value"<<value<<stauts;
    if(!value)
        return;
    qDebug()<<currentAtk()<<currentDef()<<currentSpatk()<<currentSpdef()<<currentSpeed()<<m_accuracy_level<<m_dodge_level;
    switch (stauts) {
    case PowerUpStatus::ATK:
        m_atk_level += value;
        checkStatus(m_atk_level);
        break;
    case PowerUpStatus::DEF:
        m_def_level += value;
        checkStatus(m_def_level);
        break;
    case PowerUpStatus::SPATK:
        m_spatk_level += value;
        checkStatus(m_spatk_level);
        break;
    case PowerUpStatus::SPDEF:
        m_spdef_level += value;
        checkStatus(m_spdef_level);
        break;
    case PowerUpStatus::SPEED:
        m_speed_level += value;
        checkStatus(m_speed_level);
        break;
    case PowerUpStatus::ACCURACY:
        m_accuracy_level += value;
        checkStatus(m_accuracy_level);
        break;
    case PowerUpStatus::DODGE:
        m_dodge_level += value;
        checkStatus(m_dodge_level);
        break;
    default:
        break;
    }
    qDebug()<<currentAtk()<<currentDef()<<currentSpatk()<<currentSpdef()<<currentSpeed()<<m_accuracy_level<<m_dodge_level;
}

void Pokemon::checkStatus(int &status)
{
    if(status>6)
        status=6;
    if(status<-6)
        status=-6;
}

//void Pokemon::changeStatus(int& valueToChange,int status)
//{
//    if(status == 0)
//        return;

//    valueToChange += status;

//    if(valueToChange > 6)
//        valueToChange = 6;
//    else if(valueToChange < -6)
//        valueToChange = -6;
//}

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
