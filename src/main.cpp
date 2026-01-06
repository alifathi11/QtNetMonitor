#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QJSEngine>
#include <QQmlContext>
#include <qqml.h>

#include "controllers/AuthController.h"
#include "controllers/NetworkController.h"
#include "controllers/ConfigController.h"
#include "controllers/ProfileController.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    auto* profileController = new ProfileController();
    auto* authController       = new AuthController(profileController);
    auto* configController   = new ConfigController();
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

    qmlRegisterSingletonInstance(
        "App.Profile",
        1, 0,
        "ProfileController",
        profileController
    );



    QQmlApplicationEngine engine;
    engine.load(QUrl(u"qrc:/QtNetMonitor/ui/main.qml"_qs));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}