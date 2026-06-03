#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QScreen>
#include <QApplication>
#include <QMessageBox>
#include "registr.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("registrazia.db");

    if (db.open()) {
        QSqlQuery query;
        QString createTableQuery =
            "CREATE TABLE IF NOT EXISTS users ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "username TEXT UNIQUE NOT NULL, "
            "password TEXT NOT NULL"
            ");";
        if (!query.exec(createTableQuery)) {
            qDebug() << "Ошибка создания таблицы:" << query.lastError().text();
        }
    } else {
        qDebug() << "Не удалось подключить базу данных:" << db.lastError().text();
    }

    QScreen *screen = QApplication::primaryScreen();
    if (screen) {
        QRect screenGeometry = screen->availableGeometry();
        int x = (screenGeometry.width() - this->width())/2;
        int y = (screenGeometry.height() - this->height())/2;
        this->move(x,y);
    }
    /*connect(ui->menu->actions().at(0), &QAction::triggered,this,[this]() {
        QMessageBox::information(this, "О программе", "РАботает вроде");
    });*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->close();
}



void MainWindow::on_pushButton_3_clicked()
{
    Registr *regWindow = new Registr(nullptr);

    regWindow->setWindowFlags(Qt::Window);

    regWindow->setWindowModality(Qt::ApplicationModal);

    regWindow->setAttribute(Qt::WA_DeleteOnClose);

    regWindow->show();
}


void MainWindow::on_pushButton_2_clicked()
{

}

