#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QScreen>
#include <QApplication>
#include <QMessageBox>
#include "registr.h"
#include "vxod.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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
    Registr *regWindow = new Registr(this);
    regWindow->setWindowFlags(Qt::Window);
    regWindow->setAttribute(Qt::WA_DeleteOnClose);

    this->hide();
    regWindow->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    Vxod *loginWindow = new Vxod(this);
    loginWindow->setWindowFlags(Qt::Window);
    loginWindow->setAttribute(Qt::WA_DeleteOnClose);

    this->hide();
    loginWindow->show();
}
