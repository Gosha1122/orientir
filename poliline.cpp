#include "poliline.h"


PoliLine::PoliLine(QObject *parent)
    : QObject{parent}
{}

void PoliLine::setPath(QPainterPath &path)
{
    QGraphicsPathItem::setPath(path);
}

MapControlPoint *PoliLine::getStartPoint() const
{
    return startPoint;
}

void PoliLine::setStartPoint(MapControlPoint *newStartPoint)
{
    startPoint = newStartPoint;
}

MapControlPoint *PoliLine::getFinishPoint() const
{
    return finishPoint;
}

void PoliLine::setFinishPoint(MapControlPoint *newFinishPoint)
{
    finishPoint = newFinishPoint;
}

QPointF PoliLine::getEndPoint() const
{
    return endPoint;
}

void PoliLine::setEndPoint(QPointF newEndPoint)
{
    endPoint = newEndPoint;
}
