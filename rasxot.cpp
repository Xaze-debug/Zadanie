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

double rasxot::getAmount(){
    return ui->Linerasxot->text().toDouble();
}

QString rasxot::getvid(){
    return ui->BoxVid->currentText();
}

QString rasxot::getperiod(){
    return ui->Boxperiod->currentText();
}
