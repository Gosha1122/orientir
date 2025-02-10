#include "widget.h"
#include "ui_widget.h"
#include "stylehelper.h"
#include <QAction>
#include <QGraphicsPixmapItem>
#include <QColorDialog>
#include <QAbstractItemView>
#include <QListView>
#include <QStyledItemDelegate>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    StyleHelper::setFonts();
    ui->mapPage->setStyleSheet(StyleHelper::getMapStyleDark());
    StyleHelper::setToolButtonStyleDark(ui->backButton, StyleHelper::MapIconsType::Back,false);
    StyleHelper::setToolButtonStyleDark(ui->pathButton, StyleHelper::MapIconsType::Path,false);
    StyleHelper::setToolButtonStyleDark(ui->rulerButton, StyleHelper::MapIconsType::Ruler,false);
    StyleHelper::setToolButtonStyleDark(ui->startButton, StyleHelper::MapIconsType::Start,false);
    StyleHelper::setToolButtonStyleDark(ui->moveButton, StyleHelper::MapIconsType::Move,false);
    ui->pathButton->setProperty("MapIconsType", StyleHelper::MapIconsType::Path);
    ui->rulerButton->setProperty("MapIconsType", StyleHelper::MapIconsType::Ruler);
    ui->moveButton->setProperty("MapIconsType", StyleHelper::MapIconsType::Move);
    connect(ui->pathButton, &QToolButton::clicked, this, &Widget::changCurrentToolSlot);
    connect(ui->rulerButton, &QToolButton::clicked, this, &Widget::changCurrentToolSlot);
    connect(ui->moveButton, &QToolButton::clicked, this, &Widget::changCurrentToolSlot);
    currentTool = nullptr;

    mapScene = new MapScene(this);
    mapScene->setBackgroundBrush(QColor(200,200,210));
    ui->mapView->setScene(mapScene);

    QPixmap pix(":/resourses/maps/map2.jpg");
    QGraphicsPixmapItem* imageItem = new QGraphicsPixmapItem(pix);

    ui->mapView->setSceneRect(0,0,pix.width(), pix.height());
    mapScene->addItem(imageItem);
    mapSizeValue = 100;
    connect(ui->plusButton,&QPushButton::clicked,this,&Widget::scaleSceneSlot);
    connect(ui->minusButton,&QPushButton::clicked,this,&Widget::scaleSceneSlot);
    connect(ui->lineColorButton, &QPushButton::clicked, this,&Widget::lineColorButtonSlot);


    QListView* listview = new QListView;
    QFont font = listview->font();
    font.setFamily("Comfortaa");
    font.setPointSize(10);
    listview->setFont(font);
    ui->comboBox->setView(listview);

    ui->moveButton->click();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::changCurrentToolSlot()
{
    using CType    = MapApl::CursorType;
    using MapIcons = StyleHelper::MapIconsType;
    QToolButton* btn = qobject_cast<QToolButton*>(sender());
    if(currentTool== btn)
        return;
    StyleHelper::MapIconsType type;
    if(currentTool != nullptr){
        type = static_cast<StyleHelper::MapIconsType>(currentTool->property("MapIconsType").toUInt());
        StyleHelper::setToolButtonStyleDark(currentTool, type,false);
    }
    type = static_cast<StyleHelper::MapIconsType>(btn->property("MapIconsType").toUInt());
    StyleHelper::setToolButtonStyleDark(btn, type,true);
    currentTool = btn;
    switch (type) {
    case MapIcons::Move:
        qDebug() << "lskjdf";

        ui->mapView->setCursorType(CType::OpenHand);
        ui->mapView->setDragMode(QGraphicsView::ScrollHandDrag);
        mapScene->setCurrentToolType(MapScene::ToolType::Move);
        break;
    case MapIcons::Path:
        ui->mapView->setDragMode(QGraphicsView::NoDrag);
        ui->mapView->setCursorType(CType::PathCross);
        mapScene->setCurrentToolType(MapScene::ToolType::Path);
        break;
    default:
        ui->mapView->setDragMode(QGraphicsView::NoDrag);
        ui->mapView->setCursorType(CType::PathCross);
        mapScene->setCurrentToolType(MapScene::ToolType::Default);
    }


}

void Widget::scaleSceneSlot()
{
    if(sender()->objectName()=="plusButton"){
        if(mapSizeValue >= 200){
            return;
        }
        mapSizeValue+=10;
    }else{

        if(mapSizeValue <= 0){
            return;
        }
        mapSizeValue-=10;
    }

    qreal scale = qPow(qreal(2), (mapSizeValue-100) / qreal(100));

    QTransform matrix;
    matrix.scale(scale, scale);
    matrix.rotate(0);

    ui->mapView->setTransform(matrix);
}

void Widget::lineColorButtonSlot()
{
    QColorDialog dlg(this);
    dlg.setStyleSheet("background:#555");
    QColor color = dlg.getColor(Qt::white, this,"Select");
}
