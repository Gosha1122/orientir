#include "poliline.h"

PoliLine::PoliLine(QObject *parent)
    : QObject{parent}
{}

void PoliLine::setPath(QPainterPath &path)
{
    QGraphicsPathItem::setPath(path);
}
