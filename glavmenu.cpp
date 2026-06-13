#include "glavmenu.h"
#include "ui_glavmenu.h"
#include "dbman.h"
#include "mainwindow.h"
#include "doxod.h"
#include "rasxot.h"
#include "table.h"

GlavMenu::GlavMenu(QString login, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GlavMenu)
    , m_login(login)
{
    ui->setupUi(this);

    if (!m_login.isEmpty()){
        ui->label->setText("Привет, "+ m_login+"\nНачнём работать?");
    }
}

GlavMenu::~GlavMenu()
{
    delete ui;
}


//Пока что просто проверка что БД коректно отображает юзер айди и окна могут его принтмать
void GlavMenu::on_SaveButt_clicked()
{
    int UserId = BdMan::instance().getCurrentUserId();
    QString testMessage = "Проверка связи с БД!\n";
    testMessage += "Текущий ID авторизованного юзера: " + QString::number(UserId);
    ui->textEdit->setText(testMessage);
}

//Полное закрытие программы
void GlavMenu::on_VixodButt_clicked()
{
    QApplication::quit();
}

//Разлогин
void GlavMenu::on_RazloginButt_clicked()
{
    BdMan::instance().razlogin();

    MainWindow *loginWindow = new MainWindow();
    loginWindow->show();
    this->close();
}

//Добавление нового дохода
void GlavMenu::on_DoxodButt_clicked()
{
    Doxod plusdoxodWin(this);
    int result = plusdoxodWin.exec();
    if (result == QDialog::Accepted) {
        // Здесь в будущем забираются данные из полей и будут писаться в БД

    } else if (result == QDialog::Rejected) {
        // Ничего не сохраняем, просто фиксируем закрытие
    }
}

//добавление нового расхода
void GlavMenu::on_RasxodButt_clicked()
{
    rasxot plusrasxotWin(this);
    int result = plusrasxotWin.exec();
    if (result == QDialog::Accepted) {
        // Здесь в будущем забираются данные из полей и будут писаться в БД

    } else if (result == QDialog::Rejected) {
        // Ничего не сохраняем, просто фиксируем закрытие
    }
}

//Таблица
void GlavMenu::on_TableButt_clicked()
{
    Table tableWin(this);
    int result = tableWin.exec();
    if (result == QDialog::Accepted) {
        // Здесь в будущем забираются данные из полей и будут писаться в БД

    } else if (result == QDialog::Rejected) {
        // Ничего не сохраняем, просто фиксируем закрытие
    }
}

