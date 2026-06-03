#include "vxod.h"
#include "ui_vxod.h"
#include "glavmenu.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>


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

void Vxod::on_pushButton_2_clicked()
{
    this->close();
}


void Vxod::on_pushButton_clicked()
{
    QString login = ui->lineEdit->text().trimmed();
    QString password = ui->lineEdit_2->text().trimmed();
if (login.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Внимание", "Заполните все поля для входа!");
        return;
    }
QSqlQuery query;
query.prepare("SELECT id FROM users WHERE username = :login AND password = :pass");
query.bindValue(":login", login);
query.bindValue(":pass", password);

if (query.exec()) {
    if (query.next()) {
        // Положительно
        int userId = query.value(0).toInt(); // Получаем ID пользователя из первого столбца (id)

        QMessageBox::information(this, "Успех", "Добро пожаловать, " + login + "!");

        this->close();
        //MainWindow::close();
        {
            GlavMenu *regWindow = new GlavMenu(nullptr);

            regWindow->setWindowFlags(Qt::Window);

            regWindow->setWindowModality(Qt::ApplicationModal);

            regWindow->setAttribute(Qt::WA_DeleteOnClose);

            regWindow->show();
        }
    } else {
        //положительно но
        QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль!");
    }
} else {
    // отрицательно бабах
    QMessageBox::critical(this, "Ошибка", "Сбой при проверке данных: " + query.lastError().text());
}
}

