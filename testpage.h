#ifndef TESTPAGE_H
#define TESTPAGE_H

#include <QDialog>

namespace Ui {
class testpage;
}

class testpage : public QDialog
{
    Q_OBJECT

public:
    explicit testpage(QWidget *parent = nullptr);
    ~testpage();

private slots:
    void on_pushButton_clicked();

private:
    Ui::testpage *ui;
};

#endif // TESTPAGE_H
