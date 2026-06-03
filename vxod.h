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
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Vxod *ui;
};

#endif // VXOD_H
