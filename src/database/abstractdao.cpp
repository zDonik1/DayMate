/****************************************************************************
 *
 * @author Doniyor Tokhirov <tokhirovdoniyor(at)gmail.com>
 *
 ****************************************************************************/

#include "abstractdao.h"

DaoIdType AbstractDao::m_id{ -1 };

AbstractDao::AbstractDao()
{
    m_id = getUniqueId();
}

DaoIdType AbstractDao::id()
{
    return m_id;
}
