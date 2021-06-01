/****************************************************************************
 *
 * @author Doniyor Tokhirov <tokhirovdoniyor(at)gmail.com>
 *
 ****************************************************************************/

#pragma once

#include <QObject>

class MainController : public QObject
{
    Q_OBJECT

public:
    explicit MainController(QObject *parent = nullptr);
};

