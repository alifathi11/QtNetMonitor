#include "AuthController.h"

AuthController::AuthController(QObject* parent) 
    : QObject(parent) {}

bool AuthController::loggedIn() const {
    return m_loggedIn;
}

void AuthController::signup(const QString& email, const QString& username, const QString& password) {
    if (email.isEmpty() || username.isEmpty() || password.isEmpty()) {
        emit signupFail("All fields are required.");
        return;
    }

    // validate user data

    // store user data 

    emit signupSuccess();
}

void AuthController::login(const QString& username, const QString& password) {
    // for now we can just login with username: root, password: root 
    if (username == "root" && password == "root") {
        m_loggedIn = true;
        emit loggedInChanged();
        emit loginSuccess();
    } else {
        emit loginFail("Invalid username or password.");
    }
}

