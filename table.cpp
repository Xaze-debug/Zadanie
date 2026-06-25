#include "table.h"
#include "ui_table.h"
#include <QSqlQueryModel>
#include "dbman.h"

Table::Table(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Table)
{
    ui->setupUi(this);
    m_model = new QSqlQueryModel(this);
    QString queryString = QString("SELECT type, amount, category, period, tx_date FROM transactions WHERE user_id = %1").arg(BdMan::instance().getCurrentUserId());
    m_model->setQuery(queryString, BdMan::instance().getDB());
    ui->tableView->setModel(m_model);

}

Table::~Table()
{
    delete ui;
}
