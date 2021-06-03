/****************************************************************************
 *
 * @author Doniyor Tokhirov <tokhirovdoniyor(at)gmail.com>
 *
 ****************************************************************************/

#include "abstractdao.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

DaoIdType AbstractDao::m_id{ -1 };

AbstractDao::AbstractDao()
{
    m_id = getUniqueId();
}

AbstractDao::~AbstractDao()
{
}

DaoIdType AbstractDao::id()
{
    return m_id;
}

std::pair<bool, QSqlQuery> AbstractDao::executeQuery(const QString &queryStr) const
{
    auto database = QSqlDatabase::database();
    QSqlQuery query(database);
    auto success = query.exec(queryStr);
    if (!success) {
        qWarning() << "Could not execute query with error:" << query.lastError().text();
        qWarning() << "Query text:" << queryStr;
    }
    return { success, query };
}
