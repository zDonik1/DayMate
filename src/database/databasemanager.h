/****************************************************************************
 *
 * @author Doniyor Tokhirov <tokhirovdoniyor(at)gmail.com>
 *
 ****************************************************************************/

#pragma once

#include <unordered_map>
#include <memory>

#include "abstractdao.h"

class DatabaseManager
{
    template<class DaoType>
    using EnableIfAbstractDaoDerived
    = typename std::enable_if_t<std::is_base_of<AbstractDao, DaoType>::value>;

public:
    DatabaseManager();

private:
    template<class DaoType, typename = EnableIfAbstractDaoDerived<DaoType>>
    void registerDao()
    {
        auto dao = std::make_unique<DaoType>();
        m_daos.emplace(dao->id(), std::move(dao));
    }

    void setupDatabase();

private:
    std::unordered_map<DaoIdType, std::unique_ptr<AbstractDao>> m_daos;
};
