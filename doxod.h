#ifndef DOXOD_H
#define DOXOD_H

#include <QDialog>

namespace Ui {
class Doxod;
}

class Doxod : public QDialog
{
    Q_OBJECT

public:
    explicit Doxod(QWidget *parent = nullptr);
    ~Doxod();
    double getAmount();
    QString getVid();
    QString getperiod();

private:
    Ui::Doxod *ui;
};

#endif // DOXOD_H
