#include "mapcontrolpoint.h"

MapControlPoint::MapControlPoint(QObject *parent)
    :QObject(parent), QGraphicsItem(nullptr)
{

}

QRectF MapControlPoint::boundingRect() const
{
    return QRectF(-15,-15, 30,30);
}

void MapControlPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHints(QPainter::Antialiasing);
    QPen pen(Qt::red);
    pen.setWidth(3);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);
    if(shape == Start){
        QPoint points[3]={{-15, 15},{0,-15},{15,15}};
        painter->drawPolygon(points,3);
    }else if(shape==KP){
        painter->drawEllipse(-15,-15, 30,30);
    }else if(shape==Finish){
        painter->drawEllipse(-15,-15, 30,30);
        painter->drawEllipse(-10,-10, 20,20);
    }
}

void MapControlPoint::setShape(Shape newShape)
{
    shape = newShape;
}
