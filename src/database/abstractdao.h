/****************************************************************************
 *
 * @author Doniyor Tokhirov <tokhirovdoniyor(at)gmail.com>
 *
 ****************************************************************************/

#pragma once

#include <globals.h>

class AbstractDao
{
public:
    AbstractDao();

    static DaoIdType id();

protected:
    static DaoIdType m_id;
};
