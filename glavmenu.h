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
void updateStatistics();

private slots:

    void on_SaveButt_clicked();

    void on_VixodButt_clicked();

    void on_RazloginButt_clicked();

    void on_DoxodButt_clicked();

    void on_RasxodButt_clicked();

    void on_TableButt_clicked();

private:
    Ui::GlavMenu *ui;
    QString m_login;
};

#endif // GLAVMENU_H
