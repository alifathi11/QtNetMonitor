import QtQuick
import QtQuick.Controls

import App.Auth 1.0

Page {

    title: "Login"
    
    signal signupRequested()
    
    Column { 
        anchors.centerIn: parent 
        spacing: 10 

        TextField {
            id: usernameField 
            placeholderText: "Username"
        }

        TextField {
            id: passwordField 
            placeholderText: "Password"
            echoMode: TextInput.Password
        }

        Button {
            text: "Login"
            onClicked: {
                AuthController.login(usernameField.text, passwordField.text)
            }
        }


        Button {
            text: "Sign Up"
            onClicked: {
                signupRequested()
            }
        }

        Text {
            id: error 
            color: "red"
        }
    }

    Connections {
        target: AuthController 
        function onLoginFailed(reason) {
            error.text = reason
        }
    }
}