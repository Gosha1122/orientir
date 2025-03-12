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
class QPushButton;
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
    void ColorButtonSlot();
    void settingsComboBoxSlot(int index);
    void addStartPointSlot();
    void endPathSlot();
    void backButtonSlot();
    void endButtonPointSlot();
    void openMapSlot();
    void SizeSpinBoxSlot(int value);
    void setCursorSlot(const QString& str);
private:
    Ui::Widget*  ui;
    QToolButton* currentTool;
    MapScene*    mapScene;
    int          mapSizeValue;
    QPushButton* endPathButton;




    void settingsInit();

};
#endif // WIDGET_H
