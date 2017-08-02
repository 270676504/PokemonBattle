#include "pokemon.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDir>
#include <qdebug>
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

Pokemon::Pokemon(int id)
    :AbstractPokemon(id)
{
//    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
//    for(int i=0; i<6; i++)
//    {
//        int test =qrand()%31;  //个体值

//    }
}
