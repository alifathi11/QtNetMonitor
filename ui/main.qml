import QtQuick 
import QtQuick.Controls

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
        if (authController.loggedIn) {
            mainStack.push("pages/Dashboard.qml");
        } else {
            mainStack.push("auth/AuthPage.qml");
       }
    }

    Connections {
        target: authController 
        
        function onLoginSuccess() {
            mainStack.replace("pages/Dashboard.qml")
        } 

        function onSignupSuccess() {
            mainStack.replace("pages/Dashboard.qml")
        }

        // function onLogout() {
        //     mainStack.replace("auth/AuthPage.qml")
        // }
    }
}