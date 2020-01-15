#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QMainWindow>
#include <QString>
#include <QVector>

#include "maps.h"

// статические поля класса - строки для und, hundert и zehn

class Transform
{
    const static QString hundert;
    const static QString und;
    const static QString zehn;
public:
//    Transform();

    std::tuple<Errors::ErrorCodes, QString> error(const QVector<QString> &input);
    std::tuple<Errors::ErrorCodes, QString> ger_to_arab(const QString &unit);
    std::tuple<int, QString> arab_to_slav(int arab);
    void show_error(int error_value, const QString &result);
};

#endif // TRANSFORM_H
