#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QJSEngine>
#include <QQmlContext>
#include <qqml.h>

#include "controllers/AuthController.h"
#include "controllers/NetworkController.h"
#include "controllers/ConfigController.h"


int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    auto* configController = new ConfigController();
    auto* authController = new AuthController();
    auto* networkController = new NetworkController(configController);

    qmlRegisterSingletonInstance(
        "App.Config",
        1, 0,
        "ConfigController",
        configController
    );

    qmlRegisterSingletonInstance(
        "App.Auth",
        1, 0,
        "AuthController",
        authController
    );

    qmlRegisterSingletonInstance(
        "App.Network",
        1, 0,
        "NetworkController",
        networkController
    );


    QQmlApplicationEngine engine;
    engine.load(QUrl(u"qrc:/QtNetMonitor/ui/main.qml"_qs));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}