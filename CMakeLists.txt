cmake_minimum_required(VERSION 3.16)
project(QtNetMonitorClient LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Qml
    Quick
    Network
    Sql
)

qt_add_executable(QtNetMonitorClient
    src/main.cpp
    src/controllers/AuthController.cpp
    src/controllers/NetworkController.cpp
    src/controllers/ConfigController.cpp
    src/network/NetworkClient.cpp
    src/network/MessageProtocol.cpp
    src/database/DatabaseManager.cpp
)

qt_add_qml_module(QtNetMonitorClient
    URI QtNetMonitor
    VERSION 1.0
    QML_FILES
        ui/main.qml
        ui/pages/MainPage.qml 
        ui/pages/MonitorPage.qml
        ui/pages/ConfigPage.qml
        ui/pages/ProfilePage.qml
        ui/auth/AuthPage.qml
        ui/auth/LoginPage.qml
        ui/auth/SignupPage.qml
)

target_link_libraries(QtNetMonitorClient
    PRIVATE 
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
        Qt6::Quick
        Qt6::Network
        Qt6::Sql 
)
