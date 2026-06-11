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

bool BdMan::createTables() {
    QSqlQuery query(m_db);
    const QString createTableQuery = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL
        );
    )";

    if (!query.exec(createTableQuery)) {
        qCritical() << "Ошибка создания таблицы:" << query.lastError().text();
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

void BdMan::disconnect() {
    QString connectionName = QSqlDatabase::defaultConnection;
    if (m_db.isOpen()) {
        m_db.close();
    }
    QSqlDatabase::removeDatabase(connectionName);
}

BdMan::~BdMan() {
    disconnect();
}
