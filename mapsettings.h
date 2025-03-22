#ifndef MAPSETTINGS_H
#define MAPSETTINGS_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "mapcropborderitem.h"
#include "linerpoint.h"
#include <QGraphicsLineItem>

namespace Ui {
class MapSettings;
}

class QPixmap;

class MapSettings : public QDialog
{
    Q_OBJECT

public:
    explicit MapSettings(QWidget *parent = nullptr);
    ~MapSettings();

private slots:
    void on_addButton_clicked();
    void on_cancellButton_clicked();
    void on_selectButton_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::MapSettings *ui;
    QPixmap* originImg;
    QPixmap* prevImg;

    QGraphicsScene* cropScene;
    MapCropBorderItem* cropItem;
    QGraphicsPixmapItem* pixMapItem;

    LinerPoint* point_1;
    LinerPoint* point_2;
    QGraphicsLineItem* pointsLine;
};

#endif // MAPSETTINGS_H
