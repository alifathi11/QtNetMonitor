#pragma once 

#include <QObject>

class ConfigController : public QObject { 
    Q_OBJECT 
    Q_PROPERTY(QString host READ host NOTIFY configChanged)
    Q_PROPERTY(qint16 port READ port NOTIFY configChanged)

public: 
    explicit ConfigController(QObject* parent = nullptr);

    Q_INVOKABLE void saveConfig(const QString& host, qint16 port);

    QString host() const;
    qint16 port() const;

signals: 
    void configChanged();
    void configChangeFailed(const QString& reason);
    
private: 
    QString m_host = "127.0.0.1";
    qint16  m_port =  9000;
};