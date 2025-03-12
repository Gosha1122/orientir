#include "mapcontrolpoint.h"
#include <QDebug>
#include <QMenu>
#include "mapscene.h"
#include "maplinekp.h"

MapControlPoint::MapControlPoint(QObject *parent)
    :QObject(parent), QGraphicsItem(nullptr), prevPoint(nullptr)
{

}

QRectF MapControlPoint::boundingRect() const
{
    if(shape == KP){
        return QRectF(-KPSize / 2 - penWidth / 2, -KPSize / 2 - penWidth / 2, KPSize + penWidth, KPSize + penWidth);
    }else if(shape == Start || shape == Finish){
        return QRectF(-StartSize / 2 - StartWidth / 2, -StartSize / 2 - StartWidth / 2, StartSize + StartWidth, StartSize + StartWidth);
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
        QPoint points[3];
        QPoint p1(-StartSize / 2, StartSize / 3);
        QPoint p2(0,-StartSize / 2);
        QPoint p3(StartSize / 2, StartSize / 3);
        if(finishLine != nullptr && false){
            qreal cos_a = 1 - (qPow(qAbs(finishLine->line().p1().x() - p3.x()), 2) + qPow(qAbs(finishLine->line().p1().y() - p3.y()), 2)) / (2 * qPow(StartSize * 6.25 / 12, 2));
            qreal sin_a = qSqrt(1 - cos_a * cos_a);
            qDebug() << cos_a;
            qDebug() << sin_a;
            QPoint new_p1(static_cast<int>(p1.x() * cos_a - p1.y() * sin_a), static_cast<int>(p1.x() * sin_a + p1.y() * cos_a));
            QPoint new_p2(static_cast<int>(p2.x() * cos_a - p2.y() * sin_a), static_cast<int>(p2.x() * sin_a + p2.y() * cos_a));
            QPoint new_p3(static_cast<int>(p3.x() * cos_a - p3.y() * sin_a), static_cast<int>(p3.x() * sin_a + p3.y() * cos_a));
            p1 = new_p1;
            p2 = new_p2;
            p3 = new_p3;
        }
        points[0] = p1;
        points[1] = p2;
        points[2] = p3;
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

void MapControlPoint::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(parentScene->getFinishPointFlag()){
        if(event->button()==Qt::LeftButton){
            leftButtonPresed = true;
            setPreviousPosition(event->scenePos());
            setFlag(ItemIsMovable);
        }
    }
    QGraphicsItem::mousePressEvent(event);
}

void MapControlPoint::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(leftButtonPresed){
        auto dx =  event->scenePos().x()- previousPosition.x();
        auto dy = event->scenePos().y() - previousPosition.y();
        QPointF oldPos = this->scenePos();
        moveBy(dx, dy);
        //QPointF newPos = this->scenePos();
        /*
        setPreviousPosition(event->scenePos());
        if(dx > 0.5 || dy > 0.5){
            emit moveMapPoint(oldPos, newPos);
        }
        */
        if(startLine != nullptr){
            startLine->setRKP(KPSize / 2);
            startLine->setKPLine(startLine->getStartPoint().x(), startLine->getStartPoint().y(), oldPos.x(), oldPos.y());
        }
        if(finishLine != nullptr){
            finishLine->setRKP(KPSize / 2);
            finishLine->setKPLine(oldPos.x(), oldPos.y(), finishLine->getFinishPoint().x(), finishLine->getFinishPoint().y());
        }
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void MapControlPoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        leftButtonPresed = false;
        if(startLine != nullptr){
            startLine->setKPLine(startLine->getStartPoint().x(), startLine->getStartPoint().y(), this->scenePos().x(), this->scenePos().y());
        }
        if(finishLine != nullptr){
            finishLine->setKPLine(this->scenePos().x(), this->scenePos().y(), finishLine->getFinishPoint().x(), finishLine->getFinishPoint().y());
        }
    }
    QGraphicsItem::mouseReleaseEvent(event);
}

MapLineKP *MapControlPoint::getFinishLine() const
{
    return finishLine;
}

void MapControlPoint::setFinishLine(MapLineKP *newFinishLine)
{
    finishLine = newFinishLine;
}



MapLineKP *MapControlPoint::getStartLine() const
{
    return startLine;
}

void MapControlPoint::setStartLine(MapLineKP *newStartLine)
{
    startLine = newStartLine;
}

void MapControlPoint::setParentScene(MapScene *newParentScene)
{
    parentScene = newParentScene;
}

void MapControlPoint::setPreviousPosition(QPointF pos)
{
    if(pos==previousPosition){
        return;
    }
    previousPosition = pos;
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


