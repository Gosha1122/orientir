#ifndef MAPSETTINGS_H
#define MAPSETTINGS_H

#include <QDialog>

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

private:
    Ui::MapSettings *ui;
};

#endif // MAPSETTINGS_H
