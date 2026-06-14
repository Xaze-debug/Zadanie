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

double Doxod::getAmount(){
    return ui->LineDoxod->text().toDouble();
}

QString Doxod::getVid(){
    return ui->BoxVid->currentText();
}

QString Doxod::getperiod(){
    return ui->BoxPeriod->currentText();
}
