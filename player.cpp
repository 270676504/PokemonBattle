#include "player.h"
#include "pokemon.h"
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
