#include "doxod.h"
#include "ui_doxod.h"

Doxod::Doxod(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Doxod)
{
    ui->setupUi(this);
}

Doxod::~Doxod()
{
    delete ui;
}
