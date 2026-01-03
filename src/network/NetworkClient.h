#pragma once 
#include <QObject>
#include <QTcpSocket>

class NetworkClient : public QObject {
    Q_OBJECT 

public: 
    explicit NetworkClient(QObject* parent = nullptr);

    void connectToHost(const QString& host, quint16 port);
    void disconnectFromHost();
    bool isConnected() const;

signals: 
    void connected();
    void disconnected();
    void messageReceived(const QString& message);
    void errorOccurred(const QString& error);

private slots:
    void onReadyRead();
    void onConnected();
    void onDisconnected();
    void onErrorOccurred(QAbstractSocket::SocketError error);

private:
    QTcpSocket socket;
};