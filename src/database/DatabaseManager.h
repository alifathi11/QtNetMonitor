#include <QString>
#include <QtSql/QSqlDatabase>

class DatabaseManager {
public:
    static DatabaseManager& instance();

    bool registerUser(const QString& email, const QString &username, const QString &password);
    bool loginUser(const QString &username, const QString &password);
    bool updateUser(const QString& currentUsername, const QString& username, const QString& email, const QString& password);

    std::optional<QString> getUserEmail(const QString& username);
    std::optional<QString> getUserPassword(const QString& password);

private:
    DatabaseManager();
    ~DatabaseManager();

    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    QSqlDatabase db;
    void initDatabase();
};
