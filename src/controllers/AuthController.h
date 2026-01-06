#pragma once 

#include <QObject>
#include <qtmetamacros.h>
#include "ProfileController.h"

class AuthController : public QObject {
    Q_OBJECT 

    Q_PROPERTY(bool loggedIn READ loggedIn NOTIFY loggedInChanged);

public: 
    explicit AuthController(ProfileController* profile,
                            QObject* parent = nullptr);

    Q_INVOKABLE void signup(const QString& email, const QString& username, const QString& password);
    Q_INVOKABLE void login(const QString& username, const QString& password);
    Q_INVOKABLE void logout();

    bool loggedIn() const;

signals: 
    void loginSuccess();
    void loginFailed(const QString& reason);
    void signupSuccess();
    void signupFailed(const QString& reason);
    void userLoggedOut();
    void loggedInChanged();

private: 
    bool m_loggedIn{false};
    ProfileController *m_profile;
};