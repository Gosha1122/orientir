#include "mapview.h"
#include <QDebug>
MapView::MapView(QWidget *parent):QGraphicsView(parent)
{

}

void MapView::enterEvent(QEnterEvent *event)
{
    qDebug() << "enter";
    setCursorType(cursorType);

}

void MapView::setCursorType(MapApl::CursorType newCursorType)
{
    using CType = MapApl::CursorType;
    cursorType = newCursorType;
    switch (newCursorType) {
    case CType::OpenHand:
        viewport()->setCursor(Qt::OpenHandCursor);
        break;
    case CType::PathCross:
        viewport()->setCursor(QCursor(QPixmap(":/resourses/cursors/cross-cursor-red-2.png")));
        break;
    case CType::Default:
        break;
    }
}
