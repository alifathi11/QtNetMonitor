#include "DatabaseManager.h"

#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlquery.h>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <qdir.h>
#include <qglobal.h>
#include <qsqlerror.h>
#include <qstandardpaths.h>

DatabaseManager& DatabaseManager::instance() {
    static DatabaseManager instance;
    return instance;
}

DatabaseManager::DatabaseManager() {

    const QString dbDir = QStandardPaths::writableLocation(
        QStandardPaths::AppDataLocation
    );

    QDir().mkpath(dbDir);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbDir + "/user.db");

    if (!db.open()) {
        qWarning() << "Failed to open database:" << db.lastError();
        return;
    }

    initDatabase();
}

DatabaseManager::~DatabaseManager() {
    if (db.isOpen()) {
        db.close();
    }
}

void DatabaseManager::initDatabase() {
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS users ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "email TEXT UNIQUE NOT NULL,"
               "username TEXT UNIQUE NOT NULL,"
               "password TEXT NOT NULL"
                ")"
    );
}

bool DatabaseManager::registerUser(const QString& email, const QString& username, const QString& password) {
    QSqlQuery query;
    query.prepare("INSERT INTO users (email, username, password) VALUES (?, ?, ?)");
    query.addBindValue(email);
    query.addBindValue(username);
    query.addBindValue(password); // TODO: Store hashed password 
    return query.exec();
}

bool DatabaseManager::loginUser(const QString& username, const QString& password) {
    QSqlQuery query;
    query.prepare("SELECT password FROM users WHERE username = ?");
    query.addBindValue(username);
    if (!query.exec() || !query.next()) {
        return false;
    }

    QString storedPassword = query.value(0).toString();
    return storedPassword == password; // TODO: Compare hashed passwords 
}