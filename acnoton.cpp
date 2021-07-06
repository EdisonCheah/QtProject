#include "acnoton.h"
#include "ui_acnoton.h"
#include "mainwindow.h"

AcNotOn::AcNotOn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AcNotOn)
{
    ui->setupUi(this);
}

AcNotOn::~AcNotOn()
{
    delete ui;
}

void AcNotOn::on_OkButton_clicked()
{
    close();
}

