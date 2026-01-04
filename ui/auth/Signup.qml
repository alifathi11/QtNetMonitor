import QtQuick 
import QtQuick.Controls 

Page { 

    title: "Sign Up"

    signal loginRequested()
    
    Column {
        anchors.centerIn: parent 
        spacing: 10 

        TextField {
            id: emailField 
            placeholderText: "Email"
        }

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
            text: "Sign Up"
            onClicked: {
                authController.signup(emailField.text, usernameField.text, passwordField.text);
            }
        }


        Button {
            text: "Login"
            onClicked: {
                loginRequested()
            }
        }

        Text {
            id: error 
            color: "red"
        }
    }

    Connections {
        target: authController 
        function onSignupFail(reason) {
            error.text = reason
        }
    }
}