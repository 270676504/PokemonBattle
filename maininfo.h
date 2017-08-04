#ifndef MAININFO_H
#define MAININFO_H

#include <QWidget>
#include "pokemon.h"
namespace Ui {
class MainInfo;
}

class MainInfo : public QWidget
{
    Q_OBJECT

public:
    explicit MainInfo(QWidget *parent = 0);
    explicit MainInfo(PokemonPtr pokemon, QWidget *parent = 0);
    ~MainInfo();

    void setInfo(PokemonPtr pokemon);
    void changePokemon(PokemonPtr pokemon);
    void refreshHp();
private:
    Ui::MainInfo *ui;
    PokemonPtr m_pokemon;
};

#endif // MAININFO_H
