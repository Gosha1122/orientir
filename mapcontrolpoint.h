#ifndef MAPCONTROLPOINT_H
#define MAPCONTROLPOINT_H

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QDebug>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsSceneMouseEvent>

class MapScene;
class MapLineKP;

class MapControlPoint :public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum Shape{
      Start,
      KP,
      Finish
    };
    explicit MapControlPoint(QObject* parent = nullptr);
    void setShape(Shape newShape);
    void setSettings(QColor textColor, QColor penColor, int textSize, int KPSize, int penWidth, int textStyle,
                     int StartSize, int  StartWidth, QColor StartColor, int LineWidth, QColor LineColor);

    MapControlPoint *getPrevPoint() const;
    void setPrevPoint(MapControlPoint *newPrevPoint);

    void setParentScene(MapScene *newParentScene);
    void setPreviousPosition(QPointF pos);

    MapLineKP *getStartLine() const;
    void setStartLine(MapLineKP *newStartLine);

    MapLineKP *getFinishLine() const;
    void setFinishLine(MapLineKP *newFinishLine);

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
     void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
     void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
signals:
    void removeMapPoint(MapControlPoint* point);
    void moveMapPoint(QPointF oldPos, QPointF newPos);
private:
    Shape shape;

    QColor textColor;
    QColor penColor ;
    int    textSize ;
    int    KPSize   ;
    int    penWidth  = 3;
    int    textStyle;

    QColor StartColor;
    QColor LineColor;
    int    StartSize;
    int    StartWidth;
    int    LineWidth;

    MapControlPoint* prevPoint;
    MapScene* parentScene;
    QPointF previousPosition;
    bool leftButtonPresed = false;

    MapLineKP* startLine = nullptr;
    MapLineKP* finishLine = nullptr;

};



#endif // MAPCONTROLPOINT_H
