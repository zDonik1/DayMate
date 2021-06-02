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
public:
    DatabaseManager();

private:
    template<class DaoType>
    void registerDao()
    {
        if constexpr (std::is_base_of_v<AbstractDao, DaoType>) {
            auto dao = std::make_unique<DaoType>();
            m_daos.emplace(dao->id(), std::move(dao));
        }
    }

    void setupDatabase();

private:
    std::unordered_map<DaoIdType, std::unique_ptr<AbstractDao>> m_daos;
};
