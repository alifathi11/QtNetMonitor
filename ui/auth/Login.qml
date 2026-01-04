import QtQuick
import QtQuick.Controls

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
                authController.login(usernameField.text, passwordField.text)
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
        target: authController 
        function onLoginFail(reason) {
            error.text = reason
        }
    }
}