#ifndef MAPCONTROLPOINT_H
#define MAPCONTROLPOINT_H

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QStyleOptionGraphicsItem>


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

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    Shape shape;
};

#endif // MAPCONTROLPOINT_H
