/****************************************************************************
 *
 * @author Doniyor Tokhirov <tokhirovdoniyor(at)gmail.com>
 *
 ****************************************************************************/

#pragma once

#include <QString>
#include <QSqlQuery>

#include <globals.h>

class AbstractDao
{
public:
    AbstractDao();
    virtual ~AbstractDao();

    static DaoIdType id();

protected:
    std::pair<bool, QSqlQuery> executeQuery(const QString &queryStr) const;

private:
    static DaoIdType m_id;
};
