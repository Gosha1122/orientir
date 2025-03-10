#include "mapscene.h"
#include <QDebug>
#include "mapcontrolpoint.h"
#include "poliline.h"
#include <QMenu>
#include "maplinekp.h"
MapScene::MapScene(QObject *parent)
    : QGraphicsScene{parent}
{

}

void MapScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        if(currentToolType==ToolType::Path){
            MapControlPoint* point = new MapControlPoint;
            if(!startPointFlag && !finishPointFlag){
                qDebug() << "Start";
                startPointFlag = true;

                point->setShape(MapControlPoint::Start);
                point->setSettings(KPNumColor, KPColor, KPNumSize, KPSize, KPWidth, KPNumStyle, StartSize,
                                   StartWidth, StartColor, LineWidth, LineColor);
                point->setPos(event->scenePos());
                addItem(point);

                lastItem = point;
                flagLastItemStart = true;
                oldPoint = event->scenePos();
                /*
                poliline = new PoliLine;
                QPainterPath path;
                path.moveTo(event->scenePos());
                poliline->setPath(path);
                addItem(poliline);
                */
                emit addStartPointSignal();
                pointCount ++;
            }else if(startPointFlag && !finishPointFlag){
                point->setSettings(KPNumColor, KPColor, KPNumSize, KPSize, KPWidth, KPNumStyle, StartSize,
                                   StartWidth, StartColor, LineWidth, LineColor);
                point->setShape(MapControlPoint::KP);
                point->setPos(event->scenePos());
                point->setPrevPoint(lastItem);
                addItem(point);
                qDebug() << "Kp";
                pointCount ++;
                /*
                QPainterPath path = poliline->path();
                path.lineTo(event->scenePos());
                poliline->setPath(path);
                */
                MapLineKP* line = new MapLineKP;
                line->setRKP(KPSize / 2);
                if(flagLastItemStart){
                    flagLastItemStart = false;
                    line->setFlagStartPoint(MapLineKP::StartPoint::beginStartPoint);
                    line->setRStart(StartSize / 2);
                    qDebug() << StartSize;
                }
                line->setKPLine(oldPoint.x(), oldPoint.y(), event->scenePos().x(), event->scenePos().y());
                QPen pen;
                pen.setColor(LineColor);
                pen.setWidth(LineWidth);
                line->setPen(pen);
                addItem(line);
                oldPoint = event->scenePos();



                lastItem->setFinishLine(line);
                point->setStartLine(line);

                lastItem = point;
            }else{
                qDebug() << "??";
            }
            point->setParentScene(this);
            connect(point, &MapControlPoint::removeMapPoint,
                    this, &MapScene::removeMapPointSlot);
            connect(point, &MapControlPoint::moveMapPoint,
                    this, &MapScene::moveMapPoitSlot);
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
    // if(event->button()==Qt::LeftButton){
    //     if(currentToolType==ToolType::Path){
    //         if(startPoint && !finishPoint){
    //             qDebug() << "Finish";
    //             finishPoint = true;
    //             MapControlPoint* point = new MapControlPoint;
    //             point->setSettings(KPNumColor, KPColor, KPNumSize, KPSize, KPWidth, KPNumStyle, StartSize,
    //                                StartWidth, StartColor, LineWidth, LineColor);
    //             point->setShape(MapControlPoint::Finish);
    //             point->setPos(event->scenePos());
    //             addItem(point);
    //         }
    //     }
    // }
    QGraphicsScene::mouseDoubleClickEvent(event);
}

void MapScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QGraphicsScene::contextMenuEvent(event);
    if(itemContextMenuFlag){
        itemContextMenuFlag = false;
        return;
    }
    QMenu menu;
    QAction* clearAction = menu.addAction("Очистить");
    QAction* zoomAction = menu.addAction("Увеличить");
    QAction* unzoomAction = menu.addAction("Уменьшить");
    if(pointCount == 0){
        clearAction->setEnabled(false);
    }
    QAction *selectedAction = menu.exec(event->screenPos());
    if (selectedAction == clearAction ) {
        deletePoints();
    } else if (selectedAction == zoomAction ) {
        emit zoomSignal();
    }else if (selectedAction == unzoomAction ) {
        emit unzoomSignal();
    }

}

bool MapScene::getFinishPointFlag() const
{
    return finishPointFlag;
}

void MapScene::setFinishPointFlag(bool newFinishPointFlag)
{
    finishPointFlag = newFinishPointFlag;
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
    if(flagLastItemStart){
        lastItem->getStartLine()->setFlagStartPoint(MapLineKP::StartPoint::beginAndEndStartPoint);
    }else{
        lastItem->getStartLine()->setFlagStartPoint(MapLineKP::StartPoint::endStartPoint);
    }
    lastItem->getStartLine()->setRStart(StartSize / 2);
    lastItem->getStartLine()->updateKP();
    lastItem->update();
}

void MapScene::removeMapPointSlot(MapControlPoint *point)
{
    QList<QGraphicsItem *> lst = this->items();
    /*
    for(int i=lst.size()-1;i>=0;i--){
        if(lst[i]==mapItem)
            continue;
        MapControlPoint* mp = qgraphicsitem_cast<MapControlPoint*>(lst[i]);
        if(mp->getPrevPoint()==point){
            mp->setPrevPoint(point->getPrevPoint());
        }
    }
    if(point==lastItem){
        lastItem= point->getPrevPoint();
    }
    removeItem(point);
    */
    QPointF beginPoint;
    QPointF endPoint;
    if(point->getStartLine() != nullptr){
        beginPoint = point->getStartLine()->getStartPoint();
    }else{
        endPoint = point->getFinishLine()->getFinishPoint();
        for(int i = 0; i < lst.size(); i++){
            if(lst[i] != mapItem){
                MapControlPoint* mp = qgraphicsitem_cast<MapControlPoint*>(lst[i]);
                if(mp->scenePos() == endPoint){
                    mp->setShape(MapControlPoint::Shape::Start);
                    mp->setStartLine(nullptr);
                    mp->update();
                    break;
                }
            }
        }
        removeItem(point->getFinishLine());
        removeItem(point);
        return;
    }
    if(point->getFinishLine() != nullptr){
        endPoint = point->getFinishLine()->getFinishPoint();
    }else{
        beginPoint = point->getStartLine()->getStartPoint();
        for(int i = 0; i < lst.size(); i++){
            if(lst[i] != mapItem){
                MapControlPoint* mp = qgraphicsitem_cast<MapControlPoint*>(lst[i]);
                if(mp->scenePos() == beginPoint){
                    mp->setShape(MapControlPoint::Shape::Finish);
                    mp->setFinishLine(nullptr);
                    mp->update();
                    break;
                }
            }
        }
        removeItem(point->getStartLine());
        removeItem(point);
        return;
    }
    MapLineKP* line = new MapLineKP;
    line->setRKP(KPSize / 2);
    line->setKPLine(beginPoint.x(), beginPoint.y(), endPoint.x(), endPoint.y());
    QPen pen;
    pen.setColor(LineColor);
    pen.setWidth(LineWidth);
    line->setPen(pen);
    addItem(line);

    for(int i = 0; i < lst.size(); i++){
        if(lst[i] == mapItem)
            continue;
        MapControlPoint* mp = qgraphicsitem_cast<MapControlPoint*>(lst[i]);
        if(mp->scenePos() == beginPoint){
            mp->setFinishLine(line);
        }
        if(mp->scenePos() == endPoint){
            mp->setStartLine(line);
        }
    }
    removeItem(point->getStartLine());
    removeItem(point->getFinishLine());
    removeItem(point);
}

void MapScene::moveMapPoitSlot(QPointF oldPos, QPointF newPos)
{
    QPainterPath path = poliline->path();
    QPainterPath newPath;
    for(int i=0;i<path.elementCount();i++){
        if(path.elementAt(i).x == oldPos.x() && path.elementAt(i).y == oldPos.y()){
            path.setElementPositionAt(i,newPos.x(), newPos.y());
            break;
        }
    }
    poliline->setPath(path);
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
    startPointFlag = false;
    finishPointFlag = false;
    emit removeAllMapPointsSignal();
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
