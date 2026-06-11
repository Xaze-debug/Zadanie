#ifndef VXOD_H
#define VXOD_H

#include <QWidget>

namespace Ui {
class Vxod;
}

class Vxod : public QWidget
{
    Q_OBJECT

public:
    explicit Vxod(QWidget *parent = nullptr);
    ~Vxod();

private slots:

    void on_vxodButton_clicked();

    void on_vixodButton_clicked();

private:
    Ui::Vxod *ui;
};

#endif // VXOD_H
