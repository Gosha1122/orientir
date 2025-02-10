#ifndef STYLEHELPER_H
#define STYLEHELPER_H
#include <QString>
class QToolButton;

class StyleHelper
{
public:
    enum MapIconsType{
        Back,
        Path,
        Ruler,
        Start,
        Move
    };
    StyleHelper();
    void static setFonts();
    QString static getMapStyleDark();
    void static setToolButtonStyleDark(QToolButton* btn, MapIconsType type, bool active=false);
private:
    QString static darkBgTop;
    QString static darkBgRight;

};

#endif // STYLEHELPER_H
