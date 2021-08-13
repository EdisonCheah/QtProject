#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColor>
#include <QPixmap>
#include "acnoton.h"
#include "unistd.h"
#include "thread"
#include "chrono"
#include "lightnoton.h"
#include <QSlider>

static int volumeValue = 0;
static int driverValue = 0;
static int FPassengerValue = 0;
static int RLPassengerValue = 0;
static int RRPassengerValue = 0;
static int brightnessValue = 100;
bool ProgramInitiated = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
        ui->volumeBar->setValue(volumeValue);
        ui->driverBar->setValue(driverValue);
        ui->FPassengerBar->setValue(FPassengerValue);
        ui->RLPassengerBar->setValue(RLPassengerValue);
        ui->RRPassengerBar->setValue(RRPassengerValue);
        ui->brightnessBar->setValue(brightnessValue);
        ui->brightnessSlider->setValue((QSlider::TickPosition) 100);
        QPixmap pix("/home/pi/Documents/Work/Qt Project Driving Mode Icons/comfort.png");
        ui->ComfortLabel->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio));
    ui->stackedWidget->setCurrentIndex(0);
    wiringPiSetupGpio();
    pinMode(25, INPUT);
    pinMode(18, OUTPUT);
    pinMode(17, OUTPUT);
    pinMode(4, OUTPUT);
    softPwmCreate(18, 0, 100);
    softPwmCreate(17, 0, 100);
    softPwmCreate(4, 0, 100);
    ui->brightnessSlider->setValue(brightnessValue);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool FLLightIsOn = false;
bool FCLightIsOn = false;
bool FRLightIsOn = false;
bool RLightIsOn = false;
bool HazardsLightIsOn = false;
int HeadlightSettings = 0;
bool ComfortMode = true;
bool EcoMode = false;
bool SportMode = false;
bool OffroadMode = false;

void MainWindow::on_BackButtonPg1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_BackButtonPg2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_BackButtonPg3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_BackButtonPg4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_BackButtonPg5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_BackButtonPg6_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_BackButtonPg7_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_VolumeButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_ToggleLight_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_FLLight_clicked()
{
    ProgramInitiated = true;
    if (FLLightIsOn == false) {
            ui->FLLight->setText("Front Left Light: On");
            FLLightIsOn = true;
            softPwmWrite(4, brightnessValue);
        }
        else    {
            ui->FLLight->setText("Front Left Light: Off");
            FLLightIsOn = false;
            softPwmWrite(4, 0);
        }
}

void MainWindow::on_FCLight_clicked()
{
    ProgramInitiated = true;
    if (FCLightIsOn == false) {
            ui->FCLight->setText("Front Center Light: On");
            FCLightIsOn = true;
            softPwmWrite(4, brightnessValue);
        }
        else    {
            ui->FCLight->setText("Front Center Light: Off");
            FCLightIsOn = false;
            softPwmWrite(4, 0);
        }
}


void MainWindow::on_FRLight_clicked()
{
    ProgramInitiated = true;
    if (FRLightIsOn == false) {
            ui->FRLight->setText("Front Right Light: On");
            FRLightIsOn = true;
            softPwmWrite(4, brightnessValue);
        }
        else    {
            ui->FRLight->setText("Front Right Light: Off");
            FRLightIsOn = false;
            softPwmWrite(4, 0);
        }
}


void MainWindow::on_RLight_clicked()
{
    ProgramInitiated = true;
    if (RLightIsOn == false) {
            ui->RLight->setText("Rear Light: On");
            RLightIsOn = true;
            softPwmWrite(4, brightnessValue);
        }
        else    {
            ui->RLight->setText("Rear Light: Off");
            RLightIsOn = false;
            softPwmWrite(4, 0);
        }
}


void MainWindow::on_Hazards_clicked()
{
    if (HazardsLightIsOn == false) {
            ui->Hazards->setText("Hazards: On");
            ui->Hazards->setStyleSheet("background-color: #FFA500; border:none");
            HazardsLightIsOn = true;
            softPwmWrite(17, 100);
        }
        else    {
            ui->Hazards->setText("Hazards: Off");
            ui->Hazards->setStyleSheet("background-color: #7DA1E5; border: none");
            HazardsLightIsOn = false;
            softPwmWrite(17, 0);
        }
}

void MainWindow::on_Headlights_clicked()
{
    if (HeadlightSettings == 0) {
        ui->Headlights->setText("Headlights: Low");
        ui->Headlights->setStyleSheet("background-color: #39FF14; border: none");
        softPwmWrite(18, 50);
        HeadlightSettings += 1;
    }
    else if (HeadlightSettings == 1) {
        ui->Headlights->setText("Headlights: High");
        ui->Headlights->setStyleSheet("background-color: #0000FF; border: none");
        softPwmWrite(18, 100);
        HeadlightSettings += 1;
    }
    else if (HeadlightSettings == 2) {
        ui->Headlights->setText("Headlights: Off");
        ui->Headlights->setStyleSheet("background-color: #7DA1E5; border: none");
        //digitalWrite(18, LOW);
        softPwmWrite(18, 0);
        HeadlightSettings = 0;
    }
}


void MainWindow::on_AirConButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

bool FLAcOn = false;
bool FRAcOn = false;
bool RLAcOn = false;
bool RRAcOn = false;

void MainWindow::on_FLAc_clicked()
{
    if (FLAcOn == false) {
            ui->FLAc->setText("Driver A/C: On");
            FLAcOn = true;
        }
        else    {
            ui->FLAc->setText("Driver A/C: Off");
            FLAcOn = false;
        }
}


void MainWindow::on_FRAc_clicked()
{
    if (FRAcOn == false) {
            ui->FRAc->setText("Front Passenger A/C: On");
            FRAcOn = true;
        }
        else    {
            ui->FRAc->setText("Front Passenger A/C: Off");
            FRAcOn = false;
        }
}


void MainWindow::on_RLAc_clicked()
{
    if (RLAcOn == false) {
            ui->RLAc->setText("Rear Left Passenger A/C: On");
            RLAcOn = true;
        }
        else    {
            ui->RLAc->setText("Rear Left Passenger A/C: Off");
            RLAcOn = false;
        }
}


void MainWindow::on_RRAc_clicked()
{
    if (RRAcOn == false) {
            ui->RRAc->setText("Rear Right Passenger A/C: On");
            RRAcOn = true;
        }
        else    {
            ui->RRAc->setText("Rear Right Passenger A/C: Off");
            RRAcOn = false;
        }
}

void MainWindow::on_volumeSlider_valueChanged(int value)
{
    volumeValue = value;
    ui->volumeBar->setValue(volumeValue);
}


void MainWindow::on_driverSlider_valueChanged(int value)
{
    driverValue = value;
    if (FLAcOn == true) {
        ui->driverBar->setValue(driverValue);
    }
    else    {
        AcNotOn dialog;
        dialog.setModal(true);
        dialog.exec();
    }
}


void MainWindow::on_FPassengerSlider_valueChanged(int value)
{
    FPassengerValue = value;
    if (FRAcOn == true) {
        ui->FPassengerBar->setValue(FPassengerValue);
    }
    else    {
        AcNotOn dialog;
        dialog.setModal(true);
        dialog.exec();
    }
}


void MainWindow::on_RLPassengerSlider_valueChanged(int value)
{
    RLPassengerValue = value;
    if (RLAcOn == true) {
        ui->RLPassengerBar->setValue(RLPassengerValue);
    }
    else    {
        AcNotOn dialog;
        dialog.setModal(true);
        dialog.exec();
    }
}


void MainWindow::on_RRPassengerSlider_valueChanged(int value)
{
    RRPassengerValue = value;
    if (RRAcOn == true) {
        ui->RRPassengerBar->setValue(RRPassengerValue);
    }
    else    {
        AcNotOn dialog;
        dialog.setModal(true);
        dialog.exec();
    }
}

void MainWindow::on_DrivingMode_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_AboutButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_ComfortButton_clicked()
{
    if (ComfortMode == false)   {
        QPixmap pix("/home/pi/Documents/Work/Qt Project Driving Mode Icons/comfort.png");
        ui->ComfortLabel->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio));
        QPixmap empty("");

        ui->SportLabel->setPixmap(empty);
        ui->SportButton->setStyleSheet("background-color: #264269; border: none; color: white");
        SportMode = false;

        ui->EcoLabel->setPixmap(empty);
        ui->EcoButton->setStyleSheet("background-color: #264269; border: none; color: white");
        EcoMode = false;

        ui->OffroadLabel->setPixmap(empty);
        ui->OffroadButton->setStyleSheet("background-color: #264269; border: none; color: white");
        OffroadMode = false;
    }
    else    {
        QPixmap empty("");
        ui->ComfortLabel->setPixmap(empty);
        ui->ComfortLabel->setStyleSheet("background-color: #264269; border: none; color: white");
        ComfortMode = false;
    }
}


void MainWindow::on_EcoButton_clicked()
{

    if (EcoMode == false)   {
        QPixmap pix("/home/pi/Documents/Work/Qt Project Driving Mode Icons/eco on.png");
        ui->EcoLabel->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio));
        ui->EcoButton->setStyleSheet("background-color: #39FF14; border: none; color: white");
        QPixmap empty("");

        ui->SportLabel->setPixmap(empty);
        ui->SportButton->setStyleSheet("background-color: #264269; border: none; color: white");
        SportMode = false;

        ui->ComfortLabel->setPixmap(empty);
        ui->ComfortButton->setStyleSheet("background-color: #264269; border: none; color: white");
        ComfortMode = false;

        ui->OffroadLabel->setPixmap(empty);
        ui->OffroadButton->setStyleSheet("background-color: #264269; border: none; color: white");
        OffroadMode = false;
    }
    else {
        QPixmap empty("");
        ui->EcoLabel->setPixmap(empty);
        ui->EcoButton->setStyleSheet("background-color: #7DA1E5; border: none; color: white");
        EcoMode = false;
    }
}


void MainWindow::on_SportButton_clicked()
{
    if (SportMode == false) {
        QPixmap pix("/home/pi/Documents/Work/Qt Project Driving Mode Icons/sport.png");
        ui->SportLabel->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio));
        ui->SportButton->setStyleSheet("background-color: #FF0000; border: none; color: white");
        QPixmap empty("");

        ui->ComfortLabel->setPixmap(empty);
        ui->ComfortButton->setStyleSheet("background-color: #264269; border: none; color: white");
        SportMode = false;

        ui->EcoLabel->setPixmap(empty);
        ui->EcoButton->setStyleSheet("background-color: #264269; border: none; color: white");
        EcoMode = false;

        ui->OffroadLabel->setPixmap(empty);
        ui->OffroadButton->setStyleSheet("background-color: #264269; border: none; color: white");
        OffroadMode = false;
    }
    else {
        QPixmap empty("");
        ui->SportLabel->setPixmap(empty);
        ui->SportButton->setStyleSheet("background-color: #7DA1E5; border: none; color: white");
        SportMode = false;
    }
}


void MainWindow::on_OffroadButton_clicked()
{
    if (OffroadMode == false) {
        QPixmap pix("/home/pi/Documents/Work/Qt Project Driving Mode Icons/offroad.png");
        ui->OffroadLabel->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio));
        ui->OffroadButton->setStyleSheet("background-color: #663300; border: none; color: white");
        QPixmap empty("");

        ui->SportLabel->setPixmap(empty);
        ui->SportButton->setStyleSheet("background-color: #264269; border: none; color: white");
        SportMode = false;

        ui->EcoLabel->setPixmap(empty);
        ui->EcoButton->setStyleSheet("background-color: #264269; border: none; color: white");
        EcoMode = false;

        ui->ComfortLabel->setPixmap(empty);
        ui->ComfortButton->setStyleSheet("background-color: #264269; border: none; color: white");
        OffroadMode = false;
    }
    else {
        QPixmap empty("");
        ui->OffroadLabel->setPixmap(empty);
        ui->OffroadButton->setStyleSheet("background-color: #7DA1E5; border: none; color: white");
        OffroadMode = false;
    }
}

void MainWindow::on_SettingsButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_BgColorBox_activated(int index)
{
    if (index == 0) {
        ui->stackedWidget->setStyleSheet("background-color: #264269; border: none");

        }
    else if (index == 1)    {
        ui->stackedWidget->setStyleSheet("background-color: #990000; border: none");
    }
    else if (index == 2)    {
            ui->stackedWidget->setStyleSheet("background-color: orange; border: none");
        }
    else if (index == 3)    {
            ui->stackedWidget->setStyleSheet("background-color: #FADA07; border: none");
        }
    else if (index == 4)    {
                ui->stackedWidget->setStyleSheet("background-color: green; border: none");
            }
    else if (index == 5)    {
                ui->stackedWidget->setStyleSheet("background-color: blue; border: none");
            }
    else if (index == 6)    {
                ui->stackedWidget->setStyleSheet("background-color: purple; border: none");
            }
    else if (index == 7)    {
                ui->stackedWidget->setStyleSheet("background-color: black; border: none");
            }
}

void MainWindow::on_AdjustBrightnessButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_brightnessSlider_valueChanged(int value)
{
    brightnessValue = value;
    if (FLLightIsOn == true or FRLightIsOn == true or FCLightIsOn == true or RLightIsOn == true)    {
        ui->brightnessBar->setValue(brightnessValue);
        softPwmWrite(4, brightnessValue);
    }
    else {
        if (ProgramInitiated == true)   {
            LightNotOn dialog;
            dialog.setModal(true);
            dialog.exec();
        }
        else {
        }
    }
}

void MainWindow::on_CloseButton_clicked()
{
    close();
    softPwmStop(4);
    softPwmStop(17);
    softPwmStop(18);
}
