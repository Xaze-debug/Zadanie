#ifndef GLAVMENU_H
#define GLAVMENU_H

#include <QWidget>
#include <QString>

namespace Ui {
class GlavMenu;
}

class GlavMenu : public QWidget
{
    Q_OBJECT

public:
    explicit GlavMenu(QString login="",QWidget *parent = nullptr);
    ~GlavMenu();

private slots:

    void on_SaveButt_clicked();

    void on_VixodButt_clicked();

private:
    Ui::GlavMenu *ui;
    QString m_login;
};

#endif // GLAVMENU_H
