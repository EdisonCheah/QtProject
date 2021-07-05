#include "testpage.h"
#include "ui_testpage.h"
#include "mainwindow.h"
#include "mainwindow.cpp"

static MainWindow *mainWindow;

testpage::testpage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::testpage)
{
    ui->setupUi(this);
}

testpage::~testpage()
{
    delete ui;
}

void testpage::on_pushButton_clicked()
{
    hide();
    mainWindow = new MainWindow(this);
    mainWindow->show();
}

