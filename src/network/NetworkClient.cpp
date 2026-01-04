#include "NetworkClient.h"
#include "MessageProtocol.h"
#include <qabstractsocket.h>


NetworkClient::NetworkClient(QObject* parent) 
    : QObject(parent) 
{
    connect(&m_socket, &QTcpSocket::readyRead, this, &NetworkClient::onReadyRead);
    connect(&m_socket, &QTcpSocket::connected, this, &NetworkClient::onConnected);
    connect(&m_socket, &QTcpSocket::disconnected, this, &NetworkClient::onDisconnected);
    connect(&m_socket, &QTcpSocket::errorOccurred, this, &NetworkClient::onErrorOccurred);
}

void NetworkClient::connectToHost(const QString& host, quint16 port) {
    m_socket.connectToHost(host, port);
}

void NetworkClient::disconnectFromHost() {
    m_socket.disconnectFromHost();
}

bool NetworkClient::isConnected() const {
    return m_socket.state() == QAbstractSocket::ConnectedState;
}

void NetworkClient::onReadyRead() {
    const QByteArray data = m_socket.readAll();
    const QString message = MessageProtocol::decode(data);
    emit messageReceived(message);
}

void NetworkClient::onConnected() {
    emit connected();
}

void NetworkClient::onDisconnected() {
    emit disconnected();
}

void NetworkClient::onErrorOccurred(QAbstractSocket::SocketError) {
    emit errorOccurred(m_socket.errorString());
}