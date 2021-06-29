/****************************************************************************
 *
 * @author Doniyor Tokhirov <tokhirovdoniyor(at)gmail.com>
 *
 ****************************************************************************/

#pragma once

#include <QAbstractListModel>
#include <QColor>

class ColorModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(QColor currentColor READ currentColor WRITE setCurrentColor NOTIFY currentColorChanged)
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)

public:
    explicit ColorModel(QObject *parent = nullptr);

    void setupModel(QList<QColor> &colors);
    void setAllActive(bool active = true);
    void activate(int index);
    void deactivate(int index);

    void setCurrentColor(QColor color);
    void setCurrentActiveIndex(int index);
    void setCurrentIndex(int index);


    QColor get(int index) const;
    QColor getActive(int index) const;
    Q_INVOKABLE int colorIndex(QColor color) const;

    QColor currentColor() const;
    int currentIndex() const;


    int rowCount(const QModelIndex &parent = {}) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

signals:
    void currentColorChanged();
    void currentIndexChanged();

private:
    QList<QColor> m_colors;
    QList<int> m_active;
    int m_currentIndex = -1; // true index (does not account for active colors)
};

