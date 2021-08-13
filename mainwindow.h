#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "wiringPi.h"
#include "softPwm.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_ToggleLight_clicked();

    void on_VolumeButton_clicked();

    void on_BackButtonPg1_clicked();

    void on_BackButtonPg2_clicked();

    void on_FLLight_clicked();

    void on_FCLight_clicked();

    void on_FRLight_clicked();

    void on_RLight_clicked();

    void on_Hazards_clicked();

    void on_AirConButton_clicked();

    void on_BackButtonPg3_clicked();

    void on_FLAc_clicked();

    void on_FRAc_clicked();

    void on_RLAc_clicked();

    void on_RRAc_clicked();

    void on_BackButtonPg4_clicked();

    void on_volumeSlider_valueChanged(int value);

    void on_driverSlider_valueChanged(int value);

    void on_FPassengerSlider_valueChanged(int value);

    void on_RLPassengerSlider_valueChanged(int value);

    void on_RRPassengerSlider_valueChanged(int value);

    void on_DrivingMode_clicked();

    void on_BackButtonPg5_clicked();

    void on_AboutButton_clicked();

    void on_BackButtonPg6_clicked();

    void on_Headlights_clicked();

    void on_EcoButton_clicked();

    void on_ComfortButton_clicked();

    void on_SportButton_clicked();

    void on_OffroadButton_clicked();

    void on_SettingsButton_clicked();

    void on_BgColorBox_activated(int index);

    void on_BackButtonPg7_clicked();

    void on_AdjustBrightnessButton_clicked();

    void on_brightnessSlider_valueChanged(int value);

    void on_CloseButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
