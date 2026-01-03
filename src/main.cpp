#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "app/ApplicationController.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    ApplicationController controller;

    engine.rootContext()->setContextProperty("appController", &controller);
    engine.load(QUrl(QStringLiteral("qrc:/QtNetMonitor/ui/main.qml")));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}