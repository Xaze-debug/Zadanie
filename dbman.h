#ifndef DBMAN_H
#define DBMAN_H

#include <QtSql>
#include <QDebug>

class BdMan {
public:
    static BdMan& instance() {
        static BdMan _instance;
        return _instance;
    }

    bool initDatabase(const QString& dbName);
    bool registerUser(const QString& login, const QString& password);
    bool loginUser(const QString& login, const QString& password);
    void disconnect();


    BdMan(const BdMan&) = delete;
    BdMan& operator=(const BdMan&) = delete;
    //Заопинанре входа
    int getCurrentUserId() const { return m_currentUserId; }
    void logout() { m_currentUserId = -1; }

private:
    BdMan() = default;
    ~BdMan();
    bool createTables();

    QSqlDatabase m_db;

    int m_currentUserId = -1;
};

#endif // DBMAN_H
