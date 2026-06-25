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
    updateStatistics();
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
        //Данные передаются бд
        double amount = plusdoxodWin.getAmount();
        QString Vid = plusdoxodWin.getVid();
        QString period = plusdoxodWin.getperiod();
        BdMan::instance().addTransaction("income",amount, Vid, period);
        updateStatistics();
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
        double amount = plusrasxotWin.getAmount();
        QString Vid = plusrasxotWin.getvid();
        QString period = plusrasxotWin.getperiod();
        BdMan::instance().addTransaction("expense",amount, Vid, period);
        updateStatistics();
    } else if (result == QDialog::Rejected) {
        // Ничего не сохраняем, просто фиксируем закрытие
    }
}
//Запись сумм в лейблы
void GlavMenu::updateStatistics() {
    // Получаем доступ к синглтону нашей базы данных
    BdMan& db = BdMan::instance();

    // Вытаскиваем посчитанные базой значения
    double balance = db.getCurrentBalance();
    double monthExp = db.getMonthExpenses();
    double yearExp = db.getYearExpenses();

    // Записываем их в лейблы (ВНИМАНИЕ: замени имена лейблов на свои реальные!)
    ui->labelBalance->setText("Текущий баланс: " + QString::number(balance, 'f', 2) + " ₽");
    ui->labelMonth->setText("Траты за месяц: " + QString::number(monthExp, 'f', 2) + " ₽");
    ui->labelYear->setText("Траты за год: " + QString::number(yearExp, 'f', 2) + " ₽");

    // Небольшая визуальная фишка: красим баланс в зависимости от того, в плюсе юзер или в минусе
    if (balance < 0) {
        ui->labelBalance->setStyleSheet("color: red; font-weight: bold;");
    } else {
        ui->labelBalance->setStyleSheet("color: green; font-weight: bold;");
    }
}

//Таблица
void GlavMenu::on_TableButt_clicked()
{
    Table tableWin(this);
    int result = tableWin.exec();
    // Здесь не нужно ничего забирать и писать в БД!
}



