import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import App.Auth    1.0
import App.Profile 1.0

Page {
    Column {
        spacing: 10
        anchors.centerIn: parent

        Label {
            text: "User Profile"
            font.bold: true
        }

        GridLayout {
            columns: 2
            rowSpacing: 10
            columnSpacing: 5

            Label { text: "Username:" }
            TextField {
                id: usernameField
                width: 200
                text: ProfileController.username
            }

            Label { text: "Email:" }
            TextField {
                id: emailField
                width: 200
                text: ProfileController.email
            }

            Label { text: "Password:" }
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
                AuthController.logout()
            }
        }

        Text { id: status; color: "green" }
        Text { id: error; color: "red" }
    }

    Connections {
        target: ProfileController
        function onProfileChanged() {
            status.text = "Profile updated successfully."
            error.text  = ""
        }
        function onProfileChangeFailed(reason) {
            status.text = ""
            error.text  = reason
        }
    }
}
