import QtQuick 
import QtQuick.Controls

import App.Auth 1.0

ApplicationWindow {
    id: root 
    width: 800 
    height: 600
    visible: true 

    StackView {
        id: mainStack 
        anchors.fill: parent
    } 

    Component.onCompleted: {
        if (AuthController.loggedIn) {
            mainStack.push("pages/MainPage.qml");
        } else {
            mainStack.push("auth/AuthPage.qml");
       }
    }

    Connections {
        target: AuthController 
        
        function onLoginSuccess() {
            mainStack.replace("pages/MainPage.qml")
        } 

        function onSignupSuccess() {
            mainStack.replace("pages/MainPage.qml")
        }

        function onUserLoggedOut() {
            mainStack.replace("auth/AuthPage.qml")
        }
    }
}