#pragma once 

#include <QObject>

class ProfileController : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString username READ username NOTIFY profileChanged)
    Q_PROPERTY(QString email READ email NOTIFY profileChanged)
    Q_PROPERTY(QString password READ password NOTIFY profileChanged)

public: 
    explicit ProfileController(QObject* parent = nullptr);

    Q_INVOKABLE void saveProfile(const QString& username, const QString& email, const QString& password);

    QString username() const;
    QString email() const;
    QString password() const;

    void setUsername(const QString& username);
    void setEmail(const QString& email);
    void setPassword(const QString& password);
    
signals: 
    void profileChanged();
    void profileChangeFailed(const QString& reason);

private: 
    QString m_username;
    QString m_email;
    QString m_password;
};