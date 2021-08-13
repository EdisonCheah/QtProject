#include "lightnoton.h"
#include "ui_lightnoton.h"
#include "mainwindow.h"

LightNotOn::LightNotOn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LightNotOn)
{
    ui->setupUi(this);
}

LightNotOn::~LightNotOn()
{
    delete ui;
}

void LightNotOn::on_OkButton_clicked()
{
    close();
}
