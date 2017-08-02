#include "maininfo.h"
#include "ui_maininfo.h"
#include <QString>
MainInfo::MainInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainInfo)
{
    ui->setupUi(this);
    AbstractPokemon(1);
}

MainInfo::~MainInfo()
{
    delete ui;
}

void MainInfo::setInfo(Pokemon *pokemon)
{
    if(!pokemon)
        return;
    battleStatus=pokemon->currentStatus();
    m_pokemon=pokemon;
    int level = pokemon->level();
    ui->lblLv->setText(QString::number(level));
    ui->lblName->setText(pokemon->name());
    int hpMax=(pokemon->racialValue().hp*2+pokemon->individualValue().hp)*level/100+10+level;
    int currentHp=pokemon->currentStatus().hp;
    ui->lblHp->setText(QString("%1/%2").arg(QString::number(currentHp)).arg(QString::number(hpMax)));
}
