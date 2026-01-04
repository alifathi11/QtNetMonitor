import QtQuick 
import QtQuick.Controls

Page {
    title: "QtNetMonitor Client"

    Column {
        anchors.centerIn: parent
        spacing: 10

        TextField {
            id: hostField 
            placeholderText: "Host"
            text: "127.0.0.1"
        }

        TextField {
            id: portField 
            placeholderText: "Port"
            text: "9000"
        }

        Button {
            text: appController.connected ? "Disconnect" : "connect"
            onClicked: {
                if (appController.connected) 
                    appController.disconnectFromServer()
                else 
                    appController.connectToServer(hostField.text, Number(portField.text))
            
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
            target: appController
            function onLogMessage(msg) {
                logView.text += msg + "\n"
            }
        }
    }
}

