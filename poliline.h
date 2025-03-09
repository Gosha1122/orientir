#ifndef POLILINE_H
#define POLILINE_H

#include <QObject>
#include <QGraphicsPathItem>

class PoliLine : public QObject, public QGraphicsPathItem
{
    Q_OBJECT
public:
    explicit PoliLine(QObject *parent = nullptr);
    void setPath(QPainterPath& path);

signals:
};

#endif // POLILINE_H
