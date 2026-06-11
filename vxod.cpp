#include "vxod.h"
#include "ui_vxod.h"
#include "glavmenu.h"
#include "dbman.h"
#include <QMessageBox>
#include "mainwindow.h"

Vxod::Vxod(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Vxod)
{
    ui->setupUi(this);
}

Vxod::~Vxod()
{
    delete ui;
}

void Vxod::on_vxodButton_clicked()
{
    QString login = ui->lineEdit->text().trimmed();
    QString password = ui->lineEdit_2->text().trimmed();

    if (login.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Внимание", "Заполните все поля для входа!");
        return;
    }

    if (BdMan::instance().loginUser(login, password)) {


        QMessageBox::information(this, "Успех", "Добро пожаловать, " + login + "!");

        this->close();

        GlavMenu *menuWindow = new GlavMenu(login);
        menuWindow->setWindowFlags(Qt::Window);
        menuWindow->setWindowModality(Qt::ApplicationModal);
        menuWindow->setAttribute(Qt::WA_DeleteOnClose);
        menuWindow->show();

    } else {
        QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль!");
    }
}


void Vxod::on_vixodButton_clicked()
{
    if (this->parentWidget()) {
        this->parentWidget()->show();
    }
    this->close();
}

