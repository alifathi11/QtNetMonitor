#include "AuthController.h"
#include "../database/DatabaseManager.h"
#include <cmath>
#include <optional>

AuthController::AuthController(ProfileController* profile, QObject* parent) 
    : m_profile(profile), QObject(parent) {}

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

    m_profile->setUsername(username);
    m_profile->setEmail(email);
    m_profile->setPassword(password);

    m_loggedIn = true;
    emit loggedInChanged();
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
    
    std::optional<QString> email = DatabaseManager::instance().getUserEmail(username);

    m_profile->setUsername(username);
    m_profile->setPassword(password);
    m_profile->setEmail(email->isEmpty() ? "" : email.value());

    m_loggedIn = true;
    emit loggedInChanged();
    emit loginSuccess();
}


void AuthController::logout() {

    m_profile->setUsername(NULL);
    m_profile->setPassword(NULL);
    m_profile->setEmail(NULL);

    m_loggedIn = false;
    emit userLoggedOut();
    emit loggedInChanged();
}