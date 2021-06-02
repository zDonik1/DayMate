/****************************************************************************
 *
 * @author Doniyor Tokhirov <tokhirovdoniyor(at)gmail.com>
 *
 ****************************************************************************/

#include "databasemanager.h"

#include <QSqlDatabase>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

#include "tododao.h"

DatabaseManager::DatabaseManager()
{
    setupDatabase();

    // registering daos
    registerDao<TodoDao>();
}

void DatabaseManager::setupDatabase()
{
    auto database = QSqlDatabase::addDatabase("QSQLITE");
    const auto path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(path);
    database.setDatabaseName(path + "/" + "daymate.db");
    if (!database.open()) {
        qWarning() << "Could not open database at:" << database.databaseName();
    } else {
        qInfo() << "Opened database at:" << database.databaseName();
    }
}
