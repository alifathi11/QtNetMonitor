#include "NetworkClient.h"
#include "MessageProtocol.h"
#include <qabstractsocket.h>


NetworkClient::NetworkClient(QObject* parent) 
    : QObject(parent) 
{
    connect(&socket, &QTcpSocket::readyRead, this, &NetworkClient::onReadyRead);
    connect(&socket, &QTcpSocket::connected, this, &NetworkClient::onConnected);
    connect(&socket, &QTcpSocket::disconnected, this, &NetworkClient::onDisconnected);
    connect(&socket, &QTcpSocket::errorOccurred, this, &NetworkClient::onErrorOccurred);
}

void NetworkClient::connectToHost(const QString& host, quint16 port) {
    socket.connectToHost(host, port);
}

void NetworkClient::disconnectFromHost() {
    socket.disconnectFromHost();
}

bool NetworkClient::isConnected() const {
    return socket.state() == QAbstractSocket::ConnectedState;
}

void NetworkClient::onReadyRead() {
    const QByteArray data = socket.readAll();
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
    emit errorOccurred(socket.errorString());
}