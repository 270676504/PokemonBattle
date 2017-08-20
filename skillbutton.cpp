#include "skillbutton.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include "pokemon.h"
SkillButton::SkillButton(SkillPtr skill,QGraphicsItem *parent)
    :QGraphicsWidget(parent),m_skill(skill)
{
    setAcceptHoverEvents(true);
    setCacheMode(DeviceCoordinateCache);
}

void SkillButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setPen(Qt::black);
    painter->drawRoundedRect(boundingRect(),4,4);
    painter->setFont(QFont (u8"微软雅黑",14,100));
    painter->drawText(QRect(-45,-35,90,20),Qt::AlignHCenter | Qt::AlignVCenter,m_skill->name());
    painter->drawPixmap(QRect(-40,-10,30,30),QPixmap(":/image/image/3.png"));
    painter->setFont(QFont (u8"微软雅黑",12));
    painter->drawText(QRect(-5,-15,45,20),Qt::AlignHCenter | Qt::AlignVCenter,AbstractPokemon::attributeArray[m_skill->attribute()]);
    painter->setFont(QFont (u8"微软雅黑",8));
    QString PP = QString("PP %1/%2").arg(m_skill->PPCurrent()).arg(m_skill->PPMax());
    painter->drawText(QRect(-5,5,45,10),Qt::AlignHCenter | Qt::AlignVCenter,PP);
}

QPainterPath SkillButton::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}
