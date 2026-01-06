#include "ProfileController.h"
#include "../database/DatabaseManager.h"

ProfileController::ProfileController(QObject* parent) 
    : QObject(parent) {}

void ProfileController::saveProfile(const QString& username, 
                                    const QString& email,
                                    const QString& password) 
{
    // TODO: user data validation 

    
    bool res = DatabaseManager::instance().updateUser(m_username, username, email, password);
    if (!res) {
        emit profileChangeFailed("Failed to update database.");
        return;
    }

    m_username = username;
    m_email    = email;
    m_password = password;
    
    emit profileChanged();
}

QString ProfileController::username() const {
    return m_username;
}

QString ProfileController::email() const {
    return m_email;
}

QString ProfileController::password() const {
    return m_password;
}

void ProfileController::setUsername(const QString& username) {
    m_username = username;
}

void ProfileController::setEmail(const QString& email) {
    m_email = email;
}

void ProfileController::setPassword(const QString& password) {
    m_password = password;
}