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
                point->setSettings(KPNumColor, KPColor, KPNumSize, KPSize, KPWidth, KPNumStyle, StartSize,
                                   StartWidth, StartColor, LineWidth, LineColor);
                point->setPos(event->scenePos());
                addItem(point);
                lastItem = point;
                emit addStartPointSignal();
                pointCount ++;
            }else if(startPoint && !finishPoint){
                MapControlPoint* point = new MapControlPoint;
                point->setSettings(KPNumColor, KPColor, KPNumSize, KPSize, KPWidth, KPNumStyle, StartSize,
                                   StartWidth, StartColor, LineWidth, LineColor);
                point->setShape(MapControlPoint::KP);
                point->setPos(event->scenePos());
                addItem(point);
                lastItem = point;
                qDebug() << "Kp";
                pointCount ++;
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
                MapControlPoint* point = new MapControlPoint;
                point->setSettings(KPNumColor, KPColor, KPNumSize, KPSize, KPWidth, KPNumStyle, StartSize,
                                   StartWidth, StartColor, LineWidth, LineColor);
                point->setShape(MapControlPoint::Finish);
                point->setPos(event->scenePos());
                addItem(point);
            }
        }
    }
    QGraphicsScene::mouseDoubleClickEvent(event);
}

QGraphicsItem *MapScene::getMapItem() const
{
    return mapItem;
}

void MapScene::setMapItem(QGraphicsItem *newMapItem)
{
    mapItem = newMapItem;
}

void MapScene::setFinishPoint()
{
    lastItem->setShape(MapControlPoint::Finish);
    lastItem->update();
}

int MapScene::getPointCount() const
{
    return pointCount;
}

void MapScene::deletePoints()
{
    QList<QGraphicsItem *> lst = this->items();
    for(int i=lst.size()-1;i>=0;i--){
        if(lst[i]==mapItem)
            continue;
        this->removeItem(lst[i]);
    }
    pointCount = 0;
    startPoint = false;
    finishPoint = false;
}

void MapScene::setLineColor(const QColor &newLineColor)
{
    LineColor = newLineColor;
}

void MapScene::setLineWidth(int newLineWidth)
{
    LineWidth = newLineWidth;
}

void MapScene::setStartColor(const QColor &newStartColor)
{
    StartColor = newStartColor;
}

void MapScene::setStartWidth(int newStartWidth)
{
    StartWidth = newStartWidth;
}

void MapScene::setStartSize(int newStartSize)
{
    StartSize = newStartSize;
}

void MapScene::setKPColor(const QColor &newKPColor)
{
    KPColor = newKPColor;
}

void MapScene::setKPWidth(int newKPWidth)
{
    KPWidth = newKPWidth;
}

void MapScene::setKPSize(int newKPSize)
{
    KPSize = newKPSize;
}

void MapScene::setKPNumColor(const QColor &newKPNumColor)
{
    KPNumColor = newKPNumColor;
}

void MapScene::setKPNumStyle(int newKPNumStyle)
{
    KPNumStyle = newKPNumStyle;
}

void MapScene::setKPNumSize(int newKPNumSize)
{
    KPNumSize = newKPNumSize;
}

MapScene::ToolType MapScene::getCurrentToolType() const
{
    return currentToolType;
}

void MapScene::setCurrentToolType(ToolType newCurrentToolType)
{
    currentToolType = newCurrentToolType;
}
