#include "ConfigController.h"

ConfigController::ConfigController(QObject* parent) 
    : QObject(parent) {}

void ConfigController::saveConfig(const QString& host, qint16 port) {
    m_host = host;
    m_port = port;

    emit configChanged();
}

QString ConfigController::host() const {
    return m_host;
}

qint16 ConfigController::port() const {
    return m_port;
}