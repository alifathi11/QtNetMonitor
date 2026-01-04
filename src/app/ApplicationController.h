#pragma once 
#include <QObject>
#include <qtmetamacros.h>
#include "../network/NetworkClient.h"

class ApplicationController : public QObject {
    Q_OBJECT

    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged);

public:
    explicit ApplicationController(QObject* parent = nullptr);

    bool connected() const;
    
    Q_INVOKABLE void connectToServer(const QString& host, int port);
    Q_INVOKABLE void disconnectFromServer();

signals:
    void connectedChanged();
    void logMessage(const QString& message);

private: 
    NetworkClient client;
    bool m_connected{false};
};