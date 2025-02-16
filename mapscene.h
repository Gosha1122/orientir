#ifndef MAPSCENE_H
#define MAPSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class MapScene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum class ToolType{
        Default,
        Path,
        Ruler,
        Start,
        Move
    };

    explicit MapScene(QObject *parent = nullptr);
    ToolType getCurrentToolType() const;
    void setCurrentToolType(ToolType newCurrentToolType);

    void setKPNumSize(int newKPNumSize);

    void setKPNumStyle(int newKPNumStyle);

    void setKPNumColor(const QColor &newKPNumColor);

    void setKPSize(int newKPSize);

    void setKPWidth(int newKPWidth);

    void setKPColor(const QColor &newKPColor);

    void setStartSize(int newStartSize);

    void setStartWidth(int newStartWidth);

    void setStartColor(const QColor &newStartColor);

    void setLineWidth(int newLineWidth);

    void setLineColor(const QColor &newLineColor);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

    ToolType currentToolType;
    bool startPoint = false;
    bool finishPoint = false;

    //Settings
    //Номера КП
    int    KPNumSize;
    int    KPNumStyle;
    QColor KPNumColor;
    //КП
    int    KPSize;
    int    KPWidth;
    QColor KPColor;
    //Старт/Финиш
    int    StartSize;
    int    StartWidth;
    QColor StartColor;
    //Линии
    int    LineWidth;
    QColor LineColor;


};

#endif // MAPSCENE_H
