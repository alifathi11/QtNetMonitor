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
        LoginPage {
            onSignupRequested: {
                authStack.push(signupComponent)
            }
        }
    }

    Component {
        id: signupComponent
        SignupPage {
            onLoginRequested: {
                authStack.pop()
            }
        }
    }
}