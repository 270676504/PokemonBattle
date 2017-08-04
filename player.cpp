#include "player.h"
#include "pokemon.h"
#include <QDebug>
Player::Player()
{

}

void Player::addPokemonToTeam(PokemonPtr pokemon)
{
    if(myTeam.size()<6)
        myTeam.push_back(pokemon);  // 先偷懒，后面还有
}

bool Player::hasTeam()
{
    for(PokemonPtr pokemon :myTeam)
    {
        if(pokemon->currentStatus().hp>0)
        {
            return true;
        }
    }
    qDebug("error: no pokemon can use");
    return false;
}

PokemonPtr Player::getFirstPokemon()
{
    for(PokemonPtr pokemon :myTeam)
    {
        if(pokemon->currentStatus().hp>0)
        {
            return pokemon;
        }
    }
    qDebug("error: no pokemon can use");
    return nullptr;
}

void Player::easyViewTeam()
{
    for(PokemonPtr pokemon :myTeam)
    {
       qDebug()<<pokemon->name()<<pokemon->currentStatus().hp;
    }
}

void Player::learnSkill(int index, SkillPtr skill)
{
    if(index>=myTeam.size())
    {
        qDebug()<<"add error";
         return;
    }

    auto pokemon = myTeam[index];
    pokemon->learnSkill(skill);
}
