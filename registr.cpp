#include "registr.h"
#include "ui_registr.h"
#include <qscreen.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>


Registr::Registr(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Registr)
{
    ui->setupUi(this);
    QScreen *screen = QApplication::primaryScreen();
    if (screen) {
        QRect screenGeometry = screen->availableGeometry();
        int x = (screenGeometry.width() - this->width())/2;
        int y = (screenGeometry.height() - this->height())/2;
        this->move(x,y);
    }
}

Registr::~Registr()
{
    delete ui;
}

void Registr::on_pushButton_2_clicked()
{
    this->close();
}


void Registr::on_pushButton_clicked()
{
    QString login = ui->lineEdit->text().trimmed();    //trimmed Удаляет пробелы в конце и началк
    QString password = ui->lineEdit_2->text().trimmed();

    if (login.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Внимание", "Заполните все поля!");
        return;
    }
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password) VALUES (:login, :pass)");
    query.bindValue(":login", login);
    query.bindValue(":pass", password);

    if (query.exec()) {
        QMessageBox::information(this, "Успех", "Регистрация успешно завершена!");
        this->close(); // Закрываем окно регистрации после успеха
    } else {
        if (query.lastError().nativeErrorCode() == "19") {
            QMessageBox::warning(this, "Ошибка", "Пользователь с таким логином уже существует!");
        } else {
            QMessageBox::critical(this, "Ошибка БД", "Не удалось зарегистрировать: " + query.lastError().text());
        }
    }
}

