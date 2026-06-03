#ifndef GLAVMENU_H
#define GLAVMENU_H

#include <QWidget>

namespace Ui {
class GlavMenu;
}

class GlavMenu : public QWidget
{
    Q_OBJECT

public:
    explicit GlavMenu(QWidget *parent = nullptr);
    ~GlavMenu();

private slots:
    void on_pushButton_clicked();

private:
    Ui::GlavMenu *ui;
};

#endif // GLAVMENU_H
