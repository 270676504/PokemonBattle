#include "maininfo.h"
#include "ui_maininfo.h"
#include <QString>
MainInfo::MainInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainInfo)
{
    ui->setupUi(this);
    //setAttribute(Qt::WA_TranslucentBackground, true); //背景透明，以后做好了在开
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

    ui->lblName->setText(pokemon->name());
    ui->lblLv->setText(QString::number(pokemon->level()));
    ui->lblHp->setText(QString("%1/%2").arg(QString::number(battleStatus.hp)).arg(QString::number(pokemon->hpMax())));
    ui->progressBar_hp->setValue(battleStatus.hp * 100 / pokemon->hpMax());

    auto attribute= pokemon->attribute();
    switch (attribute.size()) {
    case 1:
    ui->lblAttribute->setText(QString("%1").arg(AbstractPokemon::word_attribute[attribute[0]]));
        break;
    case 2:
    ui->lblAttribute->setText(QString("%1,%2").arg(AbstractPokemon::word_attribute[attribute[0]]).arg(AbstractPokemon::word_attribute[attribute[1]]));
        break;
    default:
        break;
    }
    //int exp = pokemon->exp();
    ui->progressBar_exp->setValue(1); //以后写,经验最大值还没定

}
