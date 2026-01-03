#pragma once 
#include <QString> 
#include <QByteArray> 

class MessageProtocol {
public: 
    static QString decode(const QByteArray& data);
    static QByteArray encode(const QString& message);
};