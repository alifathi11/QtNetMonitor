#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "app/AuthController.h"
#include "app/ApplicationController.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    AuthController authController;
    ApplicationController appController;

    engine.rootContext()->setContextProperty("authController", &authController);
    engine.rootContext()->setContextProperty("appController", &appController);
    engine.load(QUrl(QStringLiteral("qrc:/QtNetMonitor/ui/main.qml")));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}