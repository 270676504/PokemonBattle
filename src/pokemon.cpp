﻿#include "pokemon.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDir>
#include <qdebug>
#include <QTime>
#include "skill.h"
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
        query.prepare("SELECT * from Pokemon where id=:id");
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

    m_currentStatus.hp=( m_racialValue.hp*2+ m_individualValue.hp)*m_level/100+10+m_level;
    m_currentStatus.atk=(m_racialValue.atk*2+m_individualValue.atk)*m_level/100+5;
    m_currentStatus.def=(m_racialValue.def*2+m_individualValue.def)*m_level/100+5;
    m_currentStatus.spatk=(m_racialValue.spatk*2+m_individualValue.spatk)*m_level/100+5;
    m_currentStatus.spdef=(m_racialValue.spdef*2+m_individualValue.spdef)*m_level/100+5;
    m_currentStatus.speed=(m_racialValue.speed*2+m_individualValue.speed)*m_level/100+5;

    m_hpMax=(m_racialValue.hp*2+m_individualValue.hp)*m_level/100+10+m_level;
}

Pokemon::~Pokemon()
{

}

void Pokemon::hpReduce(int value)
{
    m_currentStatus.hp-=value;
    if(m_currentStatus.hp<=0)
    {
        m_currentStatus.hp=0;
    }
}

void Pokemon::learnSkill(SkillPtr skill)
{
    if(learnedSkill.size()<4)
        learnedSkill.push_back(skill); //先偷个懒，后面还有
}

void Pokemon::useSkill(int index, PokemonPtr target)
{
    qDebug()<<learnedSkill.size();
    if(index >= learnedSkill.size())
        return;
    const SkillPtr& skill =learnedSkill.at(index);
    skill->doAction(sharedFromThis(),target);
}

void Pokemon::reCalculateCurrentState()
{
    m_currentStatus.atk=(m_racialValue.atk*2+m_individualValue.atk)*m_level/100+5;
    m_currentStatus.def=(m_racialValue.def*2+m_individualValue.def)*m_level/100+5;
    m_currentStatus.spatk=(m_racialValue.spatk*2+m_individualValue.spatk)*m_level/100+5;
    m_currentStatus.spdef=(m_racialValue.spdef*2+m_individualValue.spdef)*m_level/100+5;
    m_currentStatus.speed=(m_racialValue.speed*2+m_individualValue.speed)*m_level/100+5;
}

void Pokemon::changeStatus(QByteArray status)
{
    if(status.size()<5)
        return;
    qDebug()<<currentStatus().atk<<currentStatus().def<<currentStatus().spatk<<currentStatus().spdef<<currentStatus().speed;
    changeStatus(status.at(0),m_currentStatus.atk);
    changeStatus(status.at(1),m_currentStatus.def);
    changeStatus(status.at(2),m_currentStatus.spatk);
    changeStatus(status.at(3),m_currentStatus.spdef);
    changeStatus(status.at(4),m_currentStatus.speed);
    qDebug()<<currentStatus().atk<<currentStatus().def<<currentStatus().spatk<<currentStatus().spdef<<currentStatus().speed;
}

void Pokemon::changeStatus(char status, int& valueToChange)
{
    if(status=='0')
        return;

    double coefficient=1.1;
    if(status & DEBUFF)
        coefficient=0.9;
    status |= !DEBUFF;
    for(auto i=0; i < status - '0'; i++)
    {
        valueToChange*=coefficient;
    }

}
