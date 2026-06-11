#include "registr.h"
#include "ui_registr.h"
#include "dbman.h"
#include <QScreen>
#include <QMessageBox>

Registr::Registr(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Registr)
{
    ui->setupUi(this);

    QScreen *screen = QApplication::primaryScreen();
    if (screen) {
        QRect screenGeometry = screen->availableGeometry();
        int x = (screenGeometry.width() - this->width()) / 2;
        int y = (screenGeometry.height() - this->height()) / 2;
        this->move(x, y);
    }
}

Registr::~Registr()
{
    delete ui;
}

//Регистрация пользователя
void Registr::on_registrButt_clicked()
{
    QString login = ui->lineEdit->text().trimmed();
    QString password = ui->lineEdit_2->text().trimmed();

    if (login.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Внимание", "Заполните все поля!");
        return;
    }

    if (BdMan::instance().registerUser(login, password)) {
        QMessageBox::information(this, "Успех", "Регистрация успешно завершена!");
        if (this->parentWidget()) {
            this->parentWidget()->show();
        }
        this->close();
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось зарегистрировать. Возможно, такой логин уже занят.");
    }
}

//Прост выход
void Registr::on_vixodButt_clicked()
{
    if (this->parentWidget()) {
        this->parentWidget()->show();
    }
    this->close();
}

