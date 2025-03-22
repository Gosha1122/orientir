#include "linerpoint.h"

LinerPoint::LinerPoint(QObject *parent)
    : QObject{parent}
{}

QRectF LinerPoint::boundingRect() const
{
    return QRectF(-12,-12,22,22);
}

void LinerPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(Qt::red);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(-1,-1,3,3);
    painter->setBrush(Qt::NoBrush);
    QPen pen(Qt::red);
    pen.setWidth(3);
    painter->setPen(pen);
    painter->drawEllipse(-10,-10,20,20);
}

void LinerPoint::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void LinerPoint::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

}

void LinerPoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
