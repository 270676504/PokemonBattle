#include "pokemon.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDir>
#include <qdebug>
AbstractPokemon::AbstractPokemon(int id)
    :m_id(id)
{
    QString dbFile("D:\\pokedex2.db");
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbFile);
    if(db.open())
    {
        QSqlQuery query;
        query.exec("SELECT * from Pokemon");
        if (query.next()) //存在记录
        {
//            pItem->id = query.value(i++).toInt();
//            qDebug()<<dbFile;
        }

    }



}

Pokemon::Pokemon(int id)
    :AbstractPokemon(id)
{

}
