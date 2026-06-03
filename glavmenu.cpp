#include "glavmenu.h"
#include "ui_glavmenu.h"

GlavMenu::GlavMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GlavMenu)
{
    ui->setupUi(this);
}

GlavMenu::~GlavMenu()
{
    delete ui;
}

void GlavMenu::on_pushButton_clicked()
{
    QApplication::quit();
}

