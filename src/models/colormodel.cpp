/****************************************************************************
 *
 * @author Doniyor Tokhirov <tokhirovdoniyor(at)gmail.com>
 *
 ****************************************************************************/

#include "colormodel.h"

ColorModel::ColorModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void ColorModel::setupModel(QList<QColor> &colors)
{
    beginResetModel();
    m_colors = std::move(colors);
    endResetModel();
}

void ColorModel::setAllActive(bool active)
{
    beginResetModel();
    if (active) {
        for (int i = 0; i < m_colors.size(); ++i) {
            m_active.append(i);
        }
    } else {
        m_active.clear();
    }
    endResetModel();
}

void ColorModel::activate(int index)
{
    int i = 0;
    for (; i < m_active.size(); ++i) {
        if (m_active.at(i) > index) {
            break;
        }
    }
    beginInsertRows({}, i, i);
    m_active.insert(i, index);
    endInsertRows();
}

void ColorModel::deactivate(int index)
{
    int i = 0;
    for (; i < m_active.size(); ++i) {
        if (m_active.at(i) == index) {
            break;
        }
    }
    if (i != m_active.size()) {
        beginRemoveRows({}, i, i);
        m_active.removeAt(i);
        endRemoveRows();
    }
}

void ColorModel::setCurrentColor(QColor color)
{
    setCurrentIndex(colorIndex(color));
}

void ColorModel::setCurrentActiveIndex(int index)
{
    setCurrentIndex(m_active.at(index));
}

void ColorModel::setCurrentIndex(int index)
{
    const auto prevColorIndex = createIndex(m_active.indexOf(m_currentIndex), 0);
    m_currentIndex = index;
    const auto currColorIndex = createIndex(m_active.indexOf(m_currentIndex), 0);

    dataChanged(prevColorIndex, prevColorIndex, { Qt::StatusTipRole });
    dataChanged(currColorIndex, currColorIndex, { Qt::StatusTipRole });
    emit currentIndexChanged();
    emit currentColorChanged();
}

QColor ColorModel::get(int index) const
{
    return m_colors.at(index);
}

QColor ColorModel::getActive(int index) const
{
    return m_colors.at(m_active.at(index));
}

int ColorModel::colorIndex(QColor color) const
{
    return m_colors.indexOf(color);
}

QColor ColorModel::currentColor() const
{
    return get(m_currentIndex);
}

int ColorModel::currentIndex() const
{
    return m_currentIndex;
}

int ColorModel::rowCount(const QModelIndex &/*parent*/) const
{
    return m_active.size();
}

QVariant ColorModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return {};

    switch (role) {
    case Qt::DisplayRole:
        return m_colors.at(m_active.at(index.row()));
    case Qt::DecorationRole:
        return m_colors.at(index.row()) == Qt::black;
    case Qt::StatusTipRole:
        return m_active.at(index.row()) == m_currentIndex;
    }
    return {};
}
