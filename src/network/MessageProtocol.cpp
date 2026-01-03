#include "MessageProtocol.h"
#include <qstringview.h>

QString MessageProtocol::decode(const QByteArray& data) {
    return QString::fromUtf8(data).trimmed();
}

QByteArray MessageProtocol::encode(const QString& message) {
    return message.toUtf8();
}

