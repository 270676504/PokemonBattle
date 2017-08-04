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
    explicit MainInfo(Pokemon* pokemon, QWidget *parent = 0);
    ~MainInfo();

    void setInfo(Pokemon* pokemon);
    void changePokemon(Pokemon* pokemon);
    void refreshHp();
private:
    Ui::MainInfo *ui;
    Pokemon* m_pokemon;
};

#endif // MAININFO_H
