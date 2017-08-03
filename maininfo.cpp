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

    m_pokemon=pokemon;

    ui->lblName->setText(m_pokemon->name());
    ui->lblLv->setText(QString::number(m_pokemon->level()));
    ui->lblHp->setText(QString("%1/%2").arg(QString::number(m_pokemon->currentStatus().hp)).arg(QString::number(m_pokemon->hpMax())));
    ui->progressBar_hp->setValue(m_pokemon->currentStatus().hp * 100 / m_pokemon->hpMax());

    auto attribute= m_pokemon->attribute();
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
    //int exp = m_pokemon->exp();
    ui->progressBar_exp->setValue(1); //以后写,经验最大值还没定

}

void MainInfo::refreshHp()
{
    ui->lblHp->setText(QString("%1/%2").arg(QString::number(m_pokemon->currentStatus().hp)).arg(QString::number(m_pokemon->hpMax())));
    ui->progressBar_hp->setValue(m_pokemon->currentStatus().hp * 100 / m_pokemon->hpMax());
}
