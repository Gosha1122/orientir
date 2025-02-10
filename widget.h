#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mapscene.h"
#include "defines.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
class QToolButton;
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private slots:
    void changCurrentToolSlot();
    void scaleSceneSlot();
    void lineColorButtonSlot();
private:
    Ui::Widget*  ui;
    QToolButton* currentTool;
    MapScene*    mapScene;
    int          mapSizeValue;
};
#endif // WIDGET_H
