#include "pokemon.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDir>
#include <qdebug>
#include <QTime>
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
            m_nature.push_back((AbstractPokemon::Nature)query.value(8).toInt());
            int secondary_attribute =query.value(9).toInt();
            if(secondary_attribute){
                m_nature.push_back((AbstractPokemon::Nature)secondary_attribute);
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
}
