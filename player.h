#ifndef PLAYER_H
#define PLAYER_H
#include <QVector>
#include <QSharedPointer>

class Pokemon;
typedef QSharedPointer<Pokemon> PokemonPtr;

class AbstractSkill;
typedef QSharedPointer<AbstractSkill> SkillPtr;
class Player
{
public:
    Player();
    void addPokemonToTeam(PokemonPtr pokemon);
    bool hasTeam();
    PokemonPtr getFirstPokemon();
    void easyViewTeam();
    void learnSkill(int index,SkillPtr skill);
private:
    QVector<PokemonPtr> myTeam;
    //QVector<Pokemon> myPokemons; //先不写
};

#endif // PLAYER_H
