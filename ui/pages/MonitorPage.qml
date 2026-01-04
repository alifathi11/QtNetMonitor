import QtQuick
import QtQuick.Controls

import App.Network 1.0

Page {
    Column {
        anchors.centerIn: parent
        spacing: 10

        Label {
            text: "Monitor"
            font.bold: true
        }

        Button {
            text: NetworkController.connected ? "Disconnect" : "Connect"
            onClicked: {
                if (NetworkController.connected)
                    NetworkController.disconnectFromServer()
                else
                    NetworkController.connectToServer()
            }
        }

        ScrollView {
            width: 400
            height: 200

            background: Rectangle {
                color: "#202124"
                radius: 6
            }

            TextArea {
                id: logView
                readOnly: true
                wrapMode: Text.Wrap

                background: Rectangle {
                    color: "transparent"
                }

                onTextChanged: {
                    if (!contentItem)
                        return
                    contentItem.contentY =
                        contentItem.contentHeight - contentItem.height
                }
            }
        }

        Connections {
            target: NetworkController
            function onLogMessage(msg) {
                logView.text += msg + "\n"
            }
        }
    }
}
