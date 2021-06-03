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

    template<class DaoType>
    const DaoType &getDao() const
    {
        if constexpr (std::is_base_of_v<AbstractDao, DaoType>) {
            return *dynamic_cast<DaoType *>(m_daos.at(DaoType::id()).get());
        }
    }

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
