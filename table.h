#ifndef TABLE_H
#define TABLE_H

#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class Table;
}

class Table : public QDialog
{
    Q_OBJECT

public:
    explicit Table(QWidget *parent = nullptr);
    ~Table();

private:
    Ui::Table *ui;
    QSqlQueryModel *m_model;
};

#endif // TABLE_H
