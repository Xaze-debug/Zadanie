#ifndef DBMAN_H
#define DBMAN_H

#include <QtSql>
#include <QDebug>

class BdMan {
public:
    //Синглтон
    static BdMan& instance() {
        static BdMan _instance;
        return _instance;
    }
    //Публичные методы
    bool initDatabase(const QString& dbName);
    bool registerUser(const QString& login, const QString& password);
    bool loginUser(const QString& login, const QString& password);
    void disconnect();
    void razlogin();
    bool addTransaction(const QString& type,double amount,const QString& category,const QString& period);
    double getCurrentBalance();// Доходы минус Расходы за всё время для текущего юзера
    double getMonthExpenses();// Расходы за текущий месяц
    double getYearExpenses(); // Расходы за текущий год


    //Защита Синглтона от копирования
    BdMan(const BdMan&) = delete;
    BdMan& operator=(const BdMan&) = delete;
    //Возвращение БД для таблицы
    QSqlDatabase getDB(){
        return m_db;
    }
    //Заопинанре входа
    int getCurrentUserId() const { return m_currentUserId; }
    void logout() { m_currentUserId = -1; }

private:
    BdMan() = default;
    ~BdMan();// Деструктор
    bool createTables();

    // Объект Qt, который хранит само активное соединение с базой данных
    QSqlDatabase m_db;
    //юзнрайди по умолчанию
    int m_currentUserId = -1;
};

#endif // DBMAN_H
