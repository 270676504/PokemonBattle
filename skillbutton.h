#ifndef SKILLBUTTON_H
#define SKILLBUTTON_H
#include <QGraphicsWidget>
#include "skill.h"
class SkillButton : public QGraphicsWidget
{
     Q_OBJECT
public:
    SkillButton(SkillPtr skill, QGraphicsItem *parent = 0);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) override;
    QRectF boundingRect() const override{return QRectF(-45, -35, 90, 70);}
    QPainterPath shape() const override;
    void setPix(const QPixmap &pixmap);
signals:
    void pressed();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *) override{ emit pressed();update(); }
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override{ update(); }
private:
    SkillPtr m_skill;
};



#endif // SKILLBUTTON_H
