#pragma once 

#include <QObject>
#include "../network/NetworkClient.h"
#include "ConfigController.h"

class NetworkController : public QObject {
    Q_OBJECT

    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged);

public:
    explicit NetworkController(ConfigController* config,
                               QObject* parent = nullptr);

    bool connected() const;
    
    Q_INVOKABLE void connectToServer();
    Q_INVOKABLE void disconnectFromServer();

signals:
    void connectedChanged();
    void logMessage(const QString& message);

private: 
    NetworkClient client;
    bool m_connected{false};
    ConfigController* m_config;
};