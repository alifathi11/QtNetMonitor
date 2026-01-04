#include "ApplicationController.h"

ApplicationController::ApplicationController(QObject* parent) 
    : QObject(parent)
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

    connect(&client, &NetworkClient::messageReceived, this, &ApplicationController::logMessage);

    connect(&client, &NetworkClient::errorOccurred, this, &ApplicationController::logMessage);
}

bool ApplicationController::connected() const  {
    return m_connected;
}

void ApplicationController::connectToServer(const QString& host, int port) {
    client.connectToHost(host, static_cast<quint16>(port));
}

void ApplicationController::disconnectFromServer() {
    client.disconnectFromHost();
}