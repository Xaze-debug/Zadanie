#include "glavmenu.h"
#include "ui_glavmenu.h"
#include "dbman.h"

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

