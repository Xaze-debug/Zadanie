#ifndef REGISTR_H
#define REGISTR_H

#include <QWidget>

namespace Ui {
class Registr;
}

class Registr : public QWidget
{
    Q_OBJECT

public:
    explicit Registr(QWidget *parent = nullptr);
    ~Registr();

private slots:

    void on_registrButt_clicked();

    void on_vixodButt_clicked();

private:
    Ui::Registr *ui;
};

#endif // REGISTR_H
