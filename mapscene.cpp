#include "mapscene.h"
#include <QDebug>
#include "mapcontrolpoint.h"
MapScene::MapScene(QObject *parent)
    : QGraphicsScene{parent}
{}

void MapScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        if(currentToolType==ToolType::Path){
            if(!startPoint && !finishPoint){
                qDebug() << "Start";
                startPoint = true;
                MapControlPoint* point = new MapControlPoint;
                point->setShape(MapControlPoint::Start);
                point->setPos(event->scenePos());
                addItem(point);
            }else if(startPoint && !finishPoint){
                MapControlPoint* point = new MapControlPoint;
                point->setShape(MapControlPoint::KP);
                point->setPos(event->scenePos());
                addItem(point);
                qDebug() << "Kp";
            }else{
                qDebug() << "??";
            }
        }
    }
    QGraphicsScene::mousePressEvent(event);
}

void MapScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
}

void MapScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
}

void MapScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        if(currentToolType==ToolType::Path){
            if(startPoint && !finishPoint){
                qDebug() << "Finish";
                finishPoint = true;
            }
        }
    }
    QGraphicsScene::mouseDoubleClickEvent(event);
}

MapScene::ToolType MapScene::getCurrentToolType() const
{
    return currentToolType;
}

void MapScene::setCurrentToolType(ToolType newCurrentToolType)
{
    currentToolType = newCurrentToolType;
}
