#include <QString>
#include <QtSql/QSqlDatabase>

class DatabaseManager {
public:
    static DatabaseManager& instance();

    bool registerUser(const QString& email, const QString &username, const QString &password);
    bool loginUser(const QString &username, const QString &password);

private:
    DatabaseManager();
    ~DatabaseManager();

    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    QSqlDatabase db;
    void initDatabase();
};
