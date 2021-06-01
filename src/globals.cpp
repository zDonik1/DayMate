/****************************************************************************
 *
 * @author Doniyor Tokhirov <tokhirovdoniyor(at)gmail.com>
 *
 ****************************************************************************/

#include "globals.h"

DaoIdType getUniqueId()
{
    static DaoIdType id = 0;
    return id++;
}
