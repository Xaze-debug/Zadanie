#ifndef RASXOT_H
#define RASXOT_H

#include <QDialog>

namespace Ui {
class rasxot;
}

class rasxot : public QDialog
{
    Q_OBJECT

public:
    explicit rasxot(QWidget *parent = nullptr);
    ~rasxot();
    double getAmount();
    QString getvid();
    QString getperiod();

private:
    Ui::rasxot *ui;
};

#endif // RASXOT_H
