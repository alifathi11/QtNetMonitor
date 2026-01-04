#include <QObject>
#include <qtmetamacros.h>

class AuthController : public QObject {
    Q_OBJECT 

    Q_PROPERTY(bool loggedIn READ loggedIn NOTIFY loggedInChanged);

public: 
    explicit AuthController(QObject* parent = nullptr);

    Q_INVOKABLE void signup(const QString& email, const QString& username, const QString& password);
    Q_INVOKABLE void login(const QString& username, const QString& password);

    bool loggedIn() const;

signals: 
    void loginSuccess();
    void loginFail(const QString& reason);
    void signupSuccess();
    void signupFail(const QString& reason);
    void loggedInChanged();

private: 
    bool m_loggedIn{false};
};