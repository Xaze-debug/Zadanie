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
            period TEXT NOT NULL,
            tx_date TEXT DEFAULT (date('now'))
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

//Расчёты сумм//Расчёты сумм//Расчёты сумм//Расчёты сумм//Расчёты сумм//Расчёты сумм//Расчёты сумм//Расчёты сумм//Расчёты сумм//Расчёты сумм//Расчёты сумм//Расчёты сумм//Расчёты сумм//Расчёты сумм
double BdMan::getCurrentBalance() {
    if (m_currentUserId == -1) return 0.0;

    QSqlQuery query(m_db);
    double incomes = 0.0;
    double expenses = 0.0;

    // 1. Считаем все доходы пользователя
    // ВНИМАНИЕ: Если у тебя в БД слово "Доход" пишется иначе (например, "income"), замени его здесь
    query.prepare("SELECT SUM(amount) FROM transactions WHERE user_id = :user_id AND type = 'income'");
    query.bindValue(":user_id", m_currentUserId);
    if (query.exec() && query.next()) {
        incomes = query.value(0).toDouble();
    }

    // 2. Считаем все расходы пользователя
    // ВНИМАНИЕ: Если в БД пишется "expense", замени "Расход" на "expense"
    query.prepare("SELECT SUM(amount) FROM transactions WHERE user_id = :user_id AND type = 'expense'");
    query.bindValue(":user_id", m_currentUserId);
    if (query.exec() && query.next()) {
        expenses = query.value(0).toDouble();
    }

    return incomes - expenses;
}


double BdMan::getMonthExpenses() {
    if (m_currentUserId == -1) return 0.0;

    QSqlQuery query(m_db);
    query.prepare("SELECT SUM(amount) FROM transactions WHERE user_id = :user_id AND type = 'expense' "
                  "AND strftime('%m', tx_date) = strftime('%m', 'now') "
                  "AND strftime('%Y', tx_date) = strftime('%Y', 'now')");
    query.bindValue(":user_id", m_currentUserId);

    if (query.exec() && query.next()) {
        return query.value(0).toDouble();
    }
    return 0.0;
}

double BdMan::getYearExpenses() {
    if (m_currentUserId == -1) return 0.0;

    QSqlQuery query(m_db);
    query.prepare("SELECT SUM(amount) FROM transactions WHERE user_id = :user_id AND type = 'expense' "
                  "AND strftime('%Y', tx_date) = strftime('%Y', 'now')");
    query.bindValue(":user_id", m_currentUserId);

    if (query.exec() && query.next()) {
        return query.value(0).toDouble();
    }
    return 0.0;
}
//Расчёты сумм//Расчёты сумм//Расчёты сумм//Расчёты сумм//Расчёты сумм//Расчёты сумм//Расчёты сумм//Расчёты сумм//Расчёты сумм//Расчёты сумм//Расчёты сумм//Расчёты сумм//Расчёты сумм//Расчёты сумм//Расчёты сумм//Расчёты сумм//Расчёты сумм

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
