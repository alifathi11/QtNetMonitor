import QtQuick
import QtQuick.Controls

import App.Profile 1.0

Page {
    Column {
        anchors.centerIn: parent 
        spacing: 10 

        Label {
            text: "User Profile"
            font.bold: true
        }

        Row {
            spacing: 5

            Label { text: "username: " }

            TextField {
                id: usernameField
                width: 200
                text: ProfileController.username
            }
        }

        Row {
            spacing: 5

            Label { text: "email: " }

            TextField {
                id: emailField
                width: 200
                text: ProfileController.email
            }
        }

        Row {
            spacing: 5

            Label { text: "password: " }

            TextField {
                id: passwordField
                width: 200
                text: ProfileController.password
                echoMode: TextInput.Password
            }
        }

        Button {
            text: "Save"
            onClicked: {
                ProfileController.saveProfile(
                    usernameField.text,
                    emailField.text,
                    passwordField.text
                )
            }
        }

        Button {
            text: "Logout"
            onClicked: {
                ProfileController.logout()
            }
        }

        Text {
            id: status
            color: "green"
        }

        Text {
            id: error 
            color: "red"
        }
    }

    Connections {
        target: ProfileController
        function onProfileChanged() {
            status.text = "Profile updated successfully."
            error.text  = ""
        }

        function onProfileChangeFailed(reason) {
            status.text = ""
            error.text  = reason;
        } 
    }

}