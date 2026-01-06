#include "DatabaseManager.h"

#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlquery.h>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <optional>
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

bool DatabaseManager::updateUser(const QString& currentUsername, const QString& username, const QString& email, const QString& password) {
    QSqlQuery query;
    query.prepare("UPDATE users SET username = ?, email = ?, password = ? WHERE username = ?");
    query.addBindValue(username);
    query.addBindValue(email);
    query.addBindValue(password); // TODO: Store hashed password 
    query.addBindValue(currentUsername);
    
    if (!query.exec()) return false;
    return query.numRowsAffected() > 0;
}

std::optional<QString> DatabaseManager::getUserEmail(const QString& username) {
    QSqlQuery query; 
    query.prepare("SELECT email FROM users WHERE username = ?");
    query.addBindValue(username);
    if (!query.exec() || !query.next()) {
        return std::nullopt;
    }

    return std::make_optional(query.value(0).toString());
}

std::optional<QString> DatabaseManager::getUserPassword(const QString& username) {
    QSqlQuery query; 
    query.prepare("SELECT password FROM users WHERE username = ?");
    query.addBindValue(username);
    if (!query.exec() || !query.next()) {
        return std::nullopt;
    }
    
    return std::make_optional(query.value(0).toString());
}