#include "rasxot.h"
#include "ui_rasxot.h"

rasxot::rasxot(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::rasxot)
{
    ui->setupUi(this);
}

rasxot::~rasxot()
{
    delete ui;
}
