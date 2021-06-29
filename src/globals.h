/****************************************************************************
 *
 * @author Doniyor Tokhirov <tokhirovdoniyor(at)gmail.com>
 *
 ****************************************************************************/

#pragma once

#include <QColor>

using DaoIdType = int;

DaoIdType getUniqueId();

static const QColor TODO_COLORS[] = {
    "#ecf0f1", // concrete
    "#e8a9a2", // alizarin
    "#f2e3a9", // sunflower
    "#8ecca8", // emerald
    "#99c0db", // peter river
    "#c0a3cc", // amethyst
};
