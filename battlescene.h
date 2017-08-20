#ifndef BATTLESCENE_H
#define BATTLESCENE_H
#include <QGraphicsScene>
#include "pokemon.h"
class MainInfo;

namespace Ui {
class MainWindow;
}
class BattleScene : public QGraphicsScene
{
        Q_OBJECT
    enum Person{
        Self,Oppo
    };
    enum Face{
        Front,Back
    };
public:
    BattleScene(PokemonPtr pokemon1,PokemonPtr pokemon2,QObject *parent = Q_NULLPTR);
    ~BattleScene();
    void changePokemon(PokemonPtr pokemon,Person target = Self );
protected:
    void setupUi();
    QString getGifPath(Face face,int id);
private:
    PokemonPtr m_pokemon;
    PokemonPtr oppo_pokemon;
    MainInfo* m_info;
    MainInfo* oppo_info;
};

#endif // BATTLESCENE_H
