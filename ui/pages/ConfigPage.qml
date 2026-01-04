import QtQuick
import QtQuick.Controls

import App.Config 1.0

Page {
    Column {
        anchors.centerIn: parent
        spacing: 10

        Label {
            text: "Configuration"
            font.bold: true
        }

        Row {
            spacing: 5

            Label { text: "Host:" }

            TextField {
                id: hostField
                width: 200
                text: ConfigController.host
            }
        }

        Row {
            spacing: 5

            Label { text: "Port:" }

            TextField {
                id: portField
                width: 200
                inputMethodHints: Qt.ImhDigitsOnly
                text: ConfigController.port.toString()
            }
        }

        Button {
            text: "Save"
            onClicked: {
                ConfigController.saveConfig(
                    hostField.text,
                    Number(portField.text)
                )
            }
        }

        Text {
            id: status
            color: "green"
        }
    }

    Connections {
        target: ConfigController
        function onConfigChanged() {
            status.text = "Configuration saved successfully."
        }
    }
}
