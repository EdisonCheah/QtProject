#ifndef LIGHTNOTON_H
#define LIGHTNOTON_H

#include <QDialog>

namespace Ui {
class LightNotOn;
}

class LightNotOn : public QDialog
{
    Q_OBJECT

public:
    explicit LightNotOn(QWidget *parent = nullptr);
    ~LightNotOn();

private slots:
    void on_OkButton_clicked();

private:
    Ui::LightNotOn *ui;
};

#endif // LIGHTNOTON_H
