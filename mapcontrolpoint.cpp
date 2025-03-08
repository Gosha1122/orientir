#include "mapcontrolpoint.h"
#include <QDebug>
#include <QMenu>
#include "mapscene.h"

MapControlPoint::MapControlPoint(QObject *parent)
    :QObject(parent), QGraphicsItem(nullptr), prevPoint(nullptr)
{

}

QRectF MapControlPoint::boundingRect() const
{
    if(shape == KP){
        return QRectF(-KPSize / 2, -KPSize / 2, KPSize, KPSize);
    }else if(shape == Start || shape == Finish){
        return QRectF(-StartSize / 2, -StartSize / 2, StartSize, StartSize);
    }
    return QRectF(-15, -15, 30, 30);
}

void MapControlPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHints(QPainter::Antialiasing);
    painter->setBrush(Qt::NoBrush);

    if(shape == Start){
        QPen pen(StartColor);
        pen.setWidth(StartWidth);
        painter->setPen(pen);

        QPoint points[3]={{-StartSize / 2, StartSize / 3},
                            {0,-StartSize / 2},
                            {StartSize / 2, StartSize / 3}};
        painter->drawPolygon(points, 3);
        painter->setBrush(penColor);
        painter->drawEllipse(-2, -2, 4, 4);
    }else if(shape==KP){
        QPen pen(penColor);
        pen.setWidth(penWidth);
        painter->setPen(pen);

        painter->drawEllipse(-KPSize / 2, -KPSize / 2, KPSize, KPSize);
        painter->setBrush(penColor);
        painter->drawEllipse(-2, -2, 4, 4);
    }else if(shape==Finish){
        QPen pen(StartColor);
        pen.setWidth(StartWidth);
        painter->setPen(pen);

        painter->drawEllipse(-StartSize / 2, -StartSize / 2, StartSize, StartSize);
        painter->drawEllipse(-StartSize / 3, -StartSize / 3, StartSize * 2 / 3, StartSize * 2 / 3);
        painter->setBrush(penColor);
        painter->drawEllipse(-2, -2, 4, 4);
    }
}

void MapControlPoint::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    parentScene->itemContextMenuFlag = true;
    QMenu menu;
    QAction* deleteAction = menu.addAction("Удалить");
    QAction* moveAction = menu.addAction("Переместить");
    QAction *selectedAction = menu.exec(event->screenPos());
    if (selectedAction == deleteAction ) {
        emit removeMapPoint(this);
    } else if (selectedAction == moveAction ) {
        //...
    }

}

void MapControlPoint::setParentScene(MapScene *newParentScene)
{
    parentScene = newParentScene;
}

MapControlPoint *MapControlPoint::getPrevPoint() const
{
    return prevPoint;
}

void MapControlPoint::setPrevPoint(MapControlPoint *newPrevPoint)
{
    prevPoint = newPrevPoint;
}

void MapControlPoint::setShape(Shape newShape)
{
    shape = newShape;
}

void MapControlPoint::setSettings(QColor textColor, QColor penColor, int textSize, int KPSize, int penWidth, int textStyle,
                                  int StartSize, int  StartWidth, QColor StartColor, int LineWidth, QColor LineColor)
{
    this->textColor  = textColor ;
    this->penColor   = penColor  ;
    this->textSize   = textSize  ;
    this->KPSize     = KPSize    ;
    this->penWidth   = penWidth  ;
    this->textStyle  = textStyle ;
    this->StartSize  = StartSize ;
    this->StartWidth = StartWidth;
    this->StartColor = StartColor;
    this->LineWidth  = LineWidth ;
    this->LineColor  = LineColor ;
}


