#include "stylehelper.h"
#include <QFontDatabase>
#include <QDebug>
#include <QToolButton>
#include <QPalette>
//StyleHelper::StyleHelper() {}

void StyleHelper::setFonts()
{
    int id = QFontDatabase::addApplicationFont(":/resourses/fonts/Comfortaa-Regular.ttf");
    qDebug() << QFontDatabase::applicationFontFamilies(id);
}
QString StyleHelper::darkBgTop = "#424952";
QString StyleHelper::darkBgRight = "#515A62";


QString StyleHelper::getMapStyleDark()
{
    QString comboBoxStyle =
        "QComboBox {"
        "border: 1px solid #575f62;"
        "border-radius: 5px;"
        "padding-left:10px;"
        "padding-top:3px;"
        "padding-right:10px;"
        "padding-bottom:7px;"
        "background:#323942;"
        "color:gray;"
        "min-height:20px;"
        "font-size:10pt;"
        "}"
        "QComboBox:on{"
        "color:#BFD855;"
        "}"
        "QComboBox::drop-down{"
        "border-top-right-radius:5px;"
        "border-bottom-right-radius:5px;"
        "}"
        "QComboBox::down-arrow {"
        "image: url(:/resourses/icons/down-arrow-10.png);"
        "}";
    QString comboBoxViewStyle =
        "QComboBox QAbstractItemView{"
        "outline:0px;"
        "border:none;"
        "}"
        "QAbstractItemView::item{"
        "color:#333;"
        "padding:3px 5px 5px 5px;"
        "background:#fff;"
        "}"
        "QListView::item:selected{"
        "background:#BFD855;"
        "color:#fff;"
        "}";
    return "QWidget#topPanelWidget{"
           "background:"+darkBgTop+";"
           "}"
            "QWidget#rightPanelWidget{"
            "background:"+darkBgRight+";"
            "}"
            "QSplitter::handle{"
            "background:"+darkBgRight+";"
            "}"
            "QGraphicsView{border:none;}"
            "QPushButton#plusButton{"
            "background:"+darkBgTop+";"
            "border:none;"
            "margin:0px;"
            "icon:url(:/resourses/icons/plus.svg);"
            "}"
            "QPushButton#plusButton::hover{"
            "icon:url(:/resourses/icons/plus-hover.svg);"
            "}"
            "QPushButton#minusButton{"
            "background:"+darkBgTop+";"
            "border:none;"
            "margin:0px;"
            "icon:url(:/resourses/icons/minus.svg);"
            "}"
            "QPushButton#minusButton::hover{"
            "icon:url(:/resourses/icons/minus-hover.svg);"
            "}"
            "QLabel{"
            "color:#D3D3D3;"
            "}"
            "QLabel#mapNameLabel{"
            "color:#D3D3D3;"
            "}"
            "QLabel#zoomValueLabel{"
            "color:#838383;"
            "padding-left:5px;"
            "padding-right:5px;"
            "}"
            "QTabWidget::pane { "
            "border:none;"
            "}"
            "QTabBar::tab{"
            "background:"+darkBgRight+";"
            "text-transform:uppercase;"
            "color:#D3D3D3;"
            "padding-left:0px;"
            "padding-right:0px;"
            "font-size:11pt;"
            "margin-right:20px;"
            "}"
            "QTabBar::tab:selected{"
            "color:#BFD855;"
            "border-bottom:1px solid #BFD855;"
            "}"
            "QLabel#headerLabel{"
            "background:#616A72;"
            "padding:5px;"
            "margin-top:5px;"
            "color:#a1aAb2;"
            "}"
            "QPushButton#kpTextColorButton, QPushButton#lineColorButton{"
            "border:1px solid #aab;"
            "background:red;"
            "border-radius:3px;"
            "}" + comboBoxStyle + comboBoxViewStyle;

}

void StyleHelper::setToolButtonStyleDark(QToolButton* btn, MapIconsType type, bool active){
    QString url;
    switch (type) {
    case Back:
        url = active? ":/resourses/icons/back-active.svg":":/resourses/icons/back.svg";
        break;
    case Path:
       url = active? ":/resourses/icons/path-active.svg" : ":/resourses/icons/path.svg";
        break;
    case Ruler:
        url = active? ":/resourses/icons/ruler-active.svg" :":/resourses/icons/ruler.svg";
        break;
    case Start:
        url = active? ":/resourses/icons/start-active.svg" :":/resourses/icons/start.svg";
        break;
    case Move:
        url = active? ":/resourses/icons/move-active.svg" : ":/resourses/icons/move.svg";
        break;
    }
    QString bgColor;
    QString bgColorHover = "#2B3035";
    QString textColor;

    if(active){
        bgColor = "#2B3035";
        textColor = "#BFD855";
    }else{
        bgColor = darkBgTop;
        textColor = "#D3D3D3";
    }
    btn->setStyleSheet("QToolButton{"
                       "padding-top:5px;"
                       "padding-bottom:5px;"
                       "background:"+bgColor+";"
                       "color:"+textColor+";"
                       "border:none;"
                       "}"
                       "QToolButton::hover{"
                       "background:"+bgColorHover+";"
                       "}");
    btn->setIcon(QIcon(url));
    btn->update();

}

QString StyleHelper::getEndPathButtonStyle()
{
    return "QPushButton{"
           "border:none;"
           "border-radius:5px;"
           "background:#2B3035;"
           "color:#fff;"
           "}"
           "QPushButton::hover{"
           "background:#3B4045;"
           "}"
           "QPushButton::pressed{"
           "background:#1B2025;"
           "}";
}

QString StyleHelper::getMapIconButtonStyle()
{
    return "QFrame{"
           "background:#ddd;"
           "border:2px solid #ddd;"
           "}"
           "QFrame::hover{"
           "border-color:rgb(120,150,230);"
           "}"
           "QLabel{"
           "border:none;"
           "}";
}

