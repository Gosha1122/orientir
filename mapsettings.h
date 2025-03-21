#ifndef MAPSETTINGS_H
#define MAPSETTINGS_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "mapcropborderitem.h"

namespace Ui {
class MapSettings;
}

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
    QString originPath;
    QString priveusPath;

    QGraphicsScene* cropScene;
    MapCropBorderItem* cropItem;
    QGraphicsPixmapItem* pixMapItem;
};

#endif // MAPSETTINGS_H
