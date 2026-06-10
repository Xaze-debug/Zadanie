#include "glavmenu.h"
#include "ui_glavmenu.h"

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

void GlavMenu::on_pushButton_clicked()
{
    QApplication::quit();
}

