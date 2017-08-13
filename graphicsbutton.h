﻿#ifndef GRAPHICSBUTTON_H
#define GRAPHICSBUTTON_H
#include <QGraphicsWidget>

class GraphicsButton : public QGraphicsWidget
{
    Q_OBJECT
public:
    GraphicsButton(QGraphicsItem *parent = 0);
//    GraphicsButton(/*const QPixmap &pixmap,*/ QGraphicsItem *parent = 0);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) override;
    QRectF boundingRect() const override{return QRectF(-65, -65, 130, 130);}
    QPainterPath shape() const override;
    void setPix(const QPixmap &pixmap);
signals:
    void pressed();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *) override{ emit pressed();update(); }
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override{ update(); }
private:
//    QPixmap _pix;
};

#endif // GRAPHICSBUTTON_H
