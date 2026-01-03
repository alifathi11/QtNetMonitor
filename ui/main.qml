import QtQuick 
import QtQuick.Controls

ApplicationWindow {
    width: 600
    height: 400 
    visible: true 
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

        TextArea {
            id: logView 
            width: 400 
            height: 200 
            readOnly: true
        }

        Connections {
            target: appController
            function onLogMessage(msg) {
                logView.text += msg + "\n"
            }
        }
    }
}

