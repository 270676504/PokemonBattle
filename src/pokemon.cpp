#include "pokemon.h"

AbstractPokemon::AbstractPokemon(QString name, Stature racialValue, Nature nature1, Nature nature2)
    :name(name),racialValue(racialValue),nature(nature1,nature2)
{

}

Pokemon::Pokemon(QString name, Stature racialValue, Nature nature1, Nature nature2)
    :AbstractPokemon(name,racialValue,nature1,nature2)
{

}
