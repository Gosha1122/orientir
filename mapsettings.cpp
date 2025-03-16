#include "mapsettings.h"
#include "ui_mapsettings.h"
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QPixmap>
#include <QStandardPaths>
#include <QDebug>
#include <QMessageBox>

MapSettings::MapSettings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MapSettings)
{
    ui->setupUi(this);
}

MapSettings::~MapSettings()
{
    delete ui;
}

void MapSettings::on_addButton_clicked()
{
    QString error;
    if(ui->nameEdit->text().trimmed().isEmpty()){
        error+= "Поле Название карты не может быть пустым\n";
    }
    if(ui->sizeEdit->text().trimmed().isEmpty()){
        error+= "Поле Масштаб не может быть пустым\n";
    }
    if(ui->pathEdit->text().trimmed().isEmpty()){
        error+= "Не выбрана карта\n";
    }else if(!QFile::exists(ui->pathEdit->text().trimmed())){
        error+= "Не существует изображения карты\n";
    }
    if(!error.isEmpty()){
        QMessageBox::warning(this, "Ошибка",error);
        return;
    }
    QString dirPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(dirPath);
    if(!dir.exists()){
        if(!dir.mkpath(dirPath)){
            qDebug() << "Error create dir" << dirPath;
            return;
        }
    }
    qDebug() << dirPath;
    QString path = ui->pathEdit->text().trimmed();
    if(path.isEmpty()){
        return;
    }
    QPixmap pix;
    if(pix.load(path)){
        pix.save(dirPath+"/example.png");
        QPixmap prevImg;
        if(pix.width() > pix.height()){
            prevImg = pix.scaledToWidth(300,Qt::SmoothTransformation);
        }else{
            prevImg = pix.scaledToHeight(300,Qt::SmoothTransformation);
        }
        prevImg.save(dirPath+"/prev_example.png");

    }
    this->accept();
}


void MapSettings::on_cancellButton_clicked()
{
    this->reject();
}


void MapSettings::on_selectButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Выбор изображения");
    if(path.isEmpty()){
        return;
    }
    ui->pathEdit->setText(path);
}

