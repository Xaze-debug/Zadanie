#include "dbman.h"
#include <QCryptographicHash>

bool BdMan::initDatabase(const QString& dbName) {
    if (QSqlDatabase::contains(QSqlDatabase::defaultConnection)) {
        m_db = QSqlDatabase::database();
    } else {
        m_db = QSqlDatabase::addDatabase("QSQLITE");
    }

    m_db.setDatabaseName(dbName);

    if (!m_db.open()) {
        qCritical() << "Ошибка открытия БД:" << m_db.lastError().text();
        return false;
    }

    return createTables();
}



//СОздание таблицы
bool BdMan::createTables() {
    QSqlQuery query(m_db);

    QString createUsers = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL
        );
    )";

    if (!query.exec(createUsers)) {
        qCritical() << "Ошибка создания таблицы users:" << query.lastError().text();
        return false;
    }

    QString createTransactions = R"(
        CREATE TABLE IF NOT EXISTS transactions (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER NOT NULL,
            type TEXT NOT NULL,
            amount REAL NOT NULL,
            category TEXT NOT NULL,
            period TEXT NOT NULL
        );
    )";

    if (!query.exec(createTransactions)) {
        qCritical() << "Ошибка создания таблицы transactions:" << query.lastError().text();
        return false;
    }

    return true;
}



//регистрация
bool BdMan::registerUser(const QString& login, const QString& password) {
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO users (username, password) VALUES (:login, :pass)");

    QByteArray passwordBytes = password.toUtf8();
    QString hashedPassword = QCryptographicHash::hash(passwordBytes, QCryptographicHash::Sha256).toHex();

    query.bindValue(":login", login);
    query.bindValue(":pass", hashedPassword);

    return query.exec();
}

//Добавление дохода/Расхода
bool BdMan::addTransaction(const QString& type,double amount,const QString& category,const QString& period){
    if (m_currentUserId == -1) {
        qWarning() << "Попытка добавить операцию без авторизации!";
        return false;
    }

    QSqlQuery pum(m_db);
    pum.prepare("INSERT INTO transactions (user_id, type, amount, category, period) VALUES (:user_id, :type, :amount, :category, :period)");

    pum.bindValue(":user_id", m_currentUserId);
    pum.bindValue(":type", type);
    pum.bindValue(":amount", amount);
    pum.bindValue(":category", category);
    pum.bindValue(":period", period);

    bool success = pum.exec();
    if (!success) {
        qCritical() << "Ошибка вставки транзакции:" << pum.lastError().text();
    } else {
        qDebug() << "Транзакция успешно добавлена!";
    }
    return success;
}




//вход
bool BdMan::loginUser(const QString& login, const QString& password) {
    QSqlQuery query(m_db);
    query.prepare("SELECT id FROM users WHERE username = :login AND password = :pass");

    QByteArray passwordBytes = password.toUtf8();
    QString hashedPassword = QCryptographicHash::hash(passwordBytes, QCryptographicHash::Sha256).toHex();

    query.bindValue(":login", login);
    query.bindValue(":pass", hashedPassword);

    //проверка на существование
    if (query.exec() && query.next()) {
        m_currentUserId = query.value(0).toInt();
        return true;
    }
    m_currentUserId = -1;
    return false;
}
//РАзлогин
void BdMan::razlogin(){
    this->m_currentUserId = -1;
}

void BdMan::disconnect() {
   // QString connectionName = QSqlDatabase::defaultConnection;
    if (m_db.isOpen()) {
        m_db.close();
    }
    //QSqlDatabase::removeDatabase(connectionName);

    //если я эти строчки вставлю синглтон сдохнет после отработки в main
}

BdMan::~BdMan() {
    disconnect();
}
