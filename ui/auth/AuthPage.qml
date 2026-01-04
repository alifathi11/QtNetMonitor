import QtQuick
import QtQuick.Controls 

Page {
    StackView {
        id: authStack 
        anchors.fill: parent 
        initialItem: loginComponent
    }

    Component {
        id: loginComponent
        Login {
            onSignupRequested: {
                authStack.push(signupComponent)
            }
        }
    }

    Component {
        id: signupComponent
        Signup {
            onLoginRequested: {
                authStack.pop()
            }
        }
    }
}