#include "AuthController.h"
#include "../database/DatabaseManager.h"
#include <cmath>

AuthController::AuthController(QObject* parent) 
    : QObject(parent) {}

bool AuthController::loggedIn() const {
    return m_loggedIn;
}

void AuthController::signup(const QString& email, const QString& username, const QString& password) {
    if (email.isEmpty() || username.isEmpty() || password.isEmpty()) {
        emit signupFailed("All fields are required.");
        return;
    }

    // validate user data

    // store user data 
    bool stored = DatabaseManager::instance().registerUser(email, username, password);
    if (!stored) {
        emit signupFailed("Failed to register user. Username or email may already exist.");
        return;
    }

    emit signupSuccess();
}

void AuthController::login(const QString& username, const QString& password) {
    if (username.isEmpty() || password.isEmpty()) {
        emit loginFailed("Username and password are required.");
        return;
    }

    bool loggedIn = DatabaseManager::instance().loginUser(username, password);
    if (!loggedIn) {
        emit loginFailed("Invalid username or password.");
        return; 
    } 

    m_loggedIn = true;
    emit loggedInChanged();
    emit loginSuccess();
}

