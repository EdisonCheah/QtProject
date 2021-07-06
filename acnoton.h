#ifndef ACNOTON_H
#define ACNOTON_H

#include <QDialog>

namespace Ui {
class AcNotOn;
}

class AcNotOn : public QDialog
{
    Q_OBJECT

public:
    explicit AcNotOn(QWidget *parent = nullptr);
    ~AcNotOn();

private slots:
    void on_OkButton_clicked();

private:
    Ui::AcNotOn *ui;
};

#endif // ACNOTON_H
