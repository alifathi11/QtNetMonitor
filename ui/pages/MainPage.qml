import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    title: "QtNetMonitor Client"

    ColumnLayout {
        anchors.fill: parent 
        spacing: 0

        TabBar {
            id: tabBar 
            Layout.fillWidth: true 

            TabButton { text: "Monitor" }
            TabButton { text: "Config" } 
            TabButton { text: "Profile" }
        }

        StackLayout {
            id: tabStack 
            Layout.fillWidth: true 
            Layout.fillHeight: true 
            currentIndex: tabBar.currentIndex 

            MonitorPage {}
            ConfigPage {}
            ProfilePage {}
        }
    }
}