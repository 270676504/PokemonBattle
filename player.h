#ifndef PLAYER_H
#define PLAYER_H
#include <QVector>
#include <QSharedPointer>

class Pokemon;
typedef QSharedPointer<Pokemon> PokemonPtr;

class Player
{
public:
    Player();
    void addPokemonToTeam(PokemonPtr pokemon);
    bool hasTeam();
    PokemonPtr getFirstPokemon();
private:
    QVector<PokemonPtr> myTeam;
    //QVector<Pokemon> myPokemons; //先不写
};

#endif // PLAYER_H
