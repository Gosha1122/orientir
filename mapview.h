#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QGraphicsView>
#include <QEnterEvent>
#include "defines.h"
class MapView : public QGraphicsView
{
    Q_OBJECT
public:

    explicit MapView(QWidget* parent = nullptr);


    void setCursorType(MapApl::CursorType newCursorType);

protected:
    void enterEvent(QEnterEvent* event) override;
private:
    MapApl::CursorType cursorType;
};

#endif // MAPVIEW_H
