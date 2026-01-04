#include "NetworkController.h"

NetworkController::NetworkController(ConfigController* config, QObject* parent) 
    : m_config(config), QObject(parent)
{
    connect(&client, &NetworkClient::connected, this, [this]() {
        m_connected = true;
        emit connectedChanged();
        emit logMessage("Connected to server");
    });

    connect(&client, &NetworkClient::disconnected, this, [this]() {
        m_connected = false;
        emit connectedChanged();
        emit logMessage("Disconnected from server");
    });

    connect(&client, &NetworkClient::messageReceived, this, &NetworkController::logMessage);

    connect(&client, &NetworkClient::errorOccurred, this, &NetworkController::logMessage);
}

bool NetworkController::connected() const  {
    return m_connected;
}

void NetworkController::connectToServer() {
    client.connectToHost(m_config->host(), m_config->port());
}

void NetworkController::disconnectFromServer() {
    client.disconnectFromHost();
}