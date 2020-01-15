#include "mainwindow.h"
#include "transform.h"
#include "maps.h"

#include <iostream>
#include <algorithm>
#include <QMessageBox>
#include <iterator>
#include <QLineEdit>
#include <QVector>
#include <QtCore>
#include <sstream>

const QString Transform::hundert = "hundert";
const QString Transform::und = "und";
const QString Transform::zehn = "zehn";

std::tuple<Errors::ErrorCodes, QString> Transform::ger_to_arab(const QString &unit)
{
    QVector<QString> input = QVector<QString>::fromList(unit.split(' ', QString::SkipEmptyParts));
// ~~~~~~~~~~~~~~~~~~~~~~~~~~ERRORS~~~~~~~~~~~~~~~~~~~~~~~~~~
    QString word;
    Errors::ErrorCodes error_code;
    QString error_word;
    std::tie(error_code, error_word) = error(input);

    if (error_code == Errors::ErrorCodes::NOT_FOUND)
        return std::make_tuple(error_code, error_word);

    else if (error_code == Errors::ErrorCodes::EMPTY_STRING)
        return std::make_tuple(error_code, QString(""));

    else if (error_code == Errors::ErrorCodes::ONE_DIGIT_NUMBERS)
        return std::make_tuple(error_code, QString(""));

    else if (error_code == Errors::ErrorCodes::OTHERS_NEXT_TO_UNITS)
        return std::make_tuple(error_code, QString(""));

    else if (error_code == Errors::ErrorCodes::NO_ONE_AFTER_TENS)
        return std::make_tuple(error_code, QString(""));

    else if (error_code == Errors::ErrorCodes::NO_ONE_AFTER_TENS_PLUS)
        return std::make_tuple(error_code, QString(""));

    else if (error_code == Errors::ErrorCodes::UNITS_BEFORE_UND)
        return std::make_tuple(error_code, QString(""));

    else if (error_code == Errors::ErrorCodes::TENS_AFTER_UND)
        return std::make_tuple(error_code, QString(""));

    else if (error_code == Errors::ErrorCodes::JUST_ONE_TIME)
        return std::make_tuple(error_code, error_word);

    else if (error_code == Errors::ErrorCodes::NO_ERROR)
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~1~~~~~~~~~~~~~~~~~~~~~~~~~~
    {
        if (input.size() == 1)
        {
            auto it_units = maps::units.find(input[0]);
            auto it_plus = maps::tens_plus.find(input[0]);
            auto it_tens = maps::tens.find(input[0]);

            if (it_units == maps::units.end())
            {
                if (it_plus == maps::tens_plus.end())
                {
                    if (it_tens == maps::tens.end())
                    {
                        word = input[0];
                        error(input);
                    }
                    else if (it_tens->second > 0)
                    {
                        return std::make_tuple(Errors::ErrorCodes::NO_ERROR, QString::number(it_tens->second));
                    }
                }
                else if (it_plus->second > 0)
                {
                    return std::make_tuple(Errors::ErrorCodes::NO_ERROR, QString::number(it_plus->second));
                }
            }
            else if (it_units->second > 0)
            {
                return std::make_tuple(Errors::ErrorCodes::NO_ERROR, QString::number(it_units->second));
            }
        }
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~2~~~~~~~~~~~~~~~~~~~~~~~~~~
        else if (input.size() == 2)
        {
            auto it_tens = maps::tens.find(input[0]);
            auto it_units = maps::units.find(input[0]);
            if (it_tens == maps::tens.end())
            {
                if (it_units == maps::units.end())
                {
                    word = input[0];
                    error(input);
                }
                else if (input[0] == it_units->first)
                {
                    auto it_tens = maps::tens.find(input[1]);
                    if (it_tens == maps::tens.end())
                        error(input);
                    else
                    {
                        if (input[1] == it_tens->first && it_tens->first == hundert)
                        {
                            return std::make_tuple(Errors::ErrorCodes::NO_ERROR, QString::number(it_units->second * 100));
                        }
                        else
                            error(input);
                    }
                }
            }
            else if (input[0] == it_tens->first)
            {
                if (it_tens->first == hundert)
                {
                    auto it_units = maps::units.find(input[1]);
                    auto it_plus = maps::tens_plus.find(input[1]);
                    auto it_tens = maps::tens.find(input[1]);

                    if (it_units == maps::units.end())
                    {
                        if (it_plus == maps::tens_plus.end())
                        {
                            if (it_tens == maps::tens.end())
                                error(input);
                            else if (it_tens->second > 0)
                            {
                                if (it_tens->first == hundert)
                                    error(input);
                                else
                                {
                                    return std::make_tuple(Errors::ErrorCodes::NO_ERROR, QString::number(it_tens->second + 100));
                                }
                            }
                        }
                        else if (it_plus->second > 0)
                        {
                            return std::make_tuple(Errors::ErrorCodes::NO_ERROR, QString::number(it_plus->second + 100));
                        }
                    }
                    else if (it_units->second > 0)
                    {
                        return std::make_tuple(Errors::ErrorCodes::NO_ERROR, QString::number(it_units->second + 100));
                    }
                }
                else
                    error(input);
            }
        }
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~3~~~~~~~~~~~~~~~~~~~~~~~~~~
        else if (input.size() == 3)
        {
            auto it_units = maps::units.find(input[0]);

            if (it_units == maps::units.end())
                error(input);
            else if (input[0] == it_units->first)
            {
                auto it_tens = maps::tens.find(input[1]);
                if (it_tens == maps::tens.end())
                {
                    if (input[1] == und)
                    {
                        auto it_tens = maps::tens.find(input[2]);
                        if (it_tens == maps::tens.end())
                            error(input);
                        else
                        {
                            return std::make_tuple(Errors::ErrorCodes::NO_ERROR, QString::number(it_tens->second + it_units->second));
                        }
                    }
                    else
                        error(input);
                }
                else if (input[1] == it_tens->first && it_tens->first == hundert)
                {
                    int sotni = it_units->second * 100;
                    auto it_units = maps::units.find(input[2]);
                    auto it_plus = maps::tens_plus.find(input[2]);
                    auto it_tens = maps::tens.find(input[2]);

                    if (it_units == maps::units.end())
                    {
                        if (it_plus == maps::tens_plus.end())
                        {
                            if (it_tens == maps::tens.end())
                                error(input);
                            else if (it_tens->second > 0)
                            {
                                if (it_tens->first == hundert)
                                    error(input);
                                else
                                {
                                    return std::make_tuple(Errors::ErrorCodes::NO_ERROR, QString::number(it_tens->second + sotni));
                                }
                            }
                        }
                        else if (it_plus->second > 0)
                        {
                            return std::make_tuple(Errors::ErrorCodes::NO_ERROR, QString::number(it_plus->second + sotni));
                        }
                    }
                    else if (it_units->second > 0)
                    {
                        return std::make_tuple(Errors::ErrorCodes::NO_ERROR, QString::number(it_units->second + sotni));
                    }
                }
                else
                    error(input);
            }
            else
                error(input);
        }

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~4~~~~~~~~~~~~~~~~~~~~~~~~~~
        else if (input.size() == 4)
        {
            auto it_tens = maps::tens.find(input[0]);
            if (it_tens == maps::tens.end())
                error(input);
            else
            {
                if (input[0] == it_tens->first)
                {
                    if (it_tens->first == hundert)
                    {
                        auto it_units = maps::units.find(input[1]);

                        if (it_units == maps::units.end())
                            error(input);
                        else if (input[1] == it_units->first)
                        {
                            if (input[2] == und)
                            {
                                auto it_tens = maps::tens.find(input[3]);
                                if (it_tens == maps::tens.end())
                                    error(input);
                                else
                                {
                                    if (it_tens->first == hundert)
                                        error(input);
                                    else
                                    {
                                        return std::make_tuple(Errors::ErrorCodes::NO_ERROR, QString::number(it_tens->second + it_units->second + 100));
                                    }
                                }
                            }
                            else
                                error(input);
                        }
                    }
                    else
                        error(input);
                }
                else
                    error(input);
            }
        }
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~5~~~~~~~~~~~~~~~~~~~~~~~~~~
        else if (input.size() == 5)
        {
            auto it_units = maps::units.find(input[0]);
            if (it_units == maps::units.end())
                error(input);
            else if (input[0] == it_units->first)
            {
                auto it_tens = maps::tens.find(input[1]);
                if (it_tens == maps::tens.end())
                    error(input);
                else
                {
                    if (input[1] == it_tens->first)
                    {
                        if (it_tens->first == hundert)
                        {
                            int sotni = it_units->second * 100;
                            auto it_units = maps::units.find(input[2]);

                            if (it_units == maps::units.end())
                                error(input);
                            else if (input[2] == it_units->first)
                            {
                                if (input[3] == und)
                                {
                                    auto it_tens = maps::tens.find(input[4]);
                                    if (it_tens == maps::tens.end())
                                        error(input);
                                    else
                                    {
                                        if (it_tens->first == hundert)
                                            error(input);
                                        else
                                        {
                                            return std::make_tuple(Errors::ErrorCodes::NO_ERROR, QString::number(it_tens->second + it_units->second + sotni));
                                        }
                                    }
                                }
                                else
                                    error(input);
                            }
                        }
                        else
                            error(input);
                    }
                }
            }
        }
        else
            error(input);
    }

    return std::make_tuple(Errors::ErrorCodes::NO_ERROR, QString());
}

std::tuple<int, QString> Transform::arab_to_slav(int arab)
{
    int buf = 0;
    int buf1 = 0;
    auto it = maps::slava.find(arab);
    if (arab == it->first) {
        return std::make_tuple(Errors::ErrorCodes::NO_ERROR,(it->second));
    }
    else
    {
            buf = arab % 10;
            arab -= buf;
            auto it = maps::slava.find(arab);
            if (arab == it->first)
            {
                QString first = it->second;
                auto it = maps::slava.find(buf);
                if (it == maps::slava.end())
                   return std::make_tuple(Errors::ErrorCodes::NO_ERROR,(""));
                else
                   return std::make_tuple(Errors::ErrorCodes::NO_ERROR,(first + it->second));
            }
            else
            {
                buf1 = arab % 100;
                arab -= buf1;
                auto it = maps::slava.find(arab);
                if (it == maps::slava.end())
                   return std::make_tuple(Errors::ErrorCodes::NO_ERROR,(""));
                else
                {
                    QString first = it->second;
                    auto it = maps::slava.find(buf1);
                    if (it == maps::slava.end())
                       return std::make_tuple(Errors::ErrorCodes::NO_ERROR,(""));
                    else
                    {
                        QString second = it->second;
                        auto it = maps::slava.find(buf);
                        if (it == maps::slava.end())
                           return std::make_tuple(Errors::ErrorCodes::NO_ERROR,(""));
                        else
                           return std::make_tuple(Errors::ErrorCodes::NO_ERROR,(first + second + it->second));

                    }
                }
            }

        }
    }

std::tuple<Errors::ErrorCodes, QString> Transform::error(const QVector<QString> &input)
{
    for (auto it = input.begin(); it <= input.end(); it++)
    {
        if (it == input.end())
        {
            return std::make_tuple(Errors::ErrorCodes::EMPTY_STRING, QString());
        }
        else
        {
            auto it_units = maps::units.find(*it);
            auto it_tens = maps::tens.find(*it);
            auto it_plus = maps::tens_plus.find(*it);

            if (it_units == maps::units.end())
            {
                if (it_plus == maps::tens_plus.end())
                {
                    if (it_tens == maps::tens.end())
                    {
                        if (*it != und)
                        {
                            return std::make_tuple(Errors::ErrorCodes::NOT_FOUND, *it);
                        }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~если und
                        else if (*it == und)
                        {
                            for (auto i = it + 1; i < input.end(); i++)
                            {
                                if (*i == und)
                                    return std::make_tuple(Errors::ErrorCodes::JUST_ONE_TIME, und);
                                else
                                    continue;
                            }
                            if (it == input.begin())
                                return std::make_tuple(Errors::ErrorCodes::UNITS_BEFORE_UND, QString());
                            else
                            {
                                auto it0 = it - 1;

                                    auto it_units = maps::units.find(*it0);
                                    auto it_tens = maps::tens.find(*it0);
                                    auto it_plus = maps::tens_plus.find(*it0);

                                    if (it_units == maps::units.end())
                                    {
                                        if (it_plus == maps::tens_plus.end())
                                        {
                                            if (it_tens == maps::tens.end())
                                                return std::make_tuple(Errors::ErrorCodes::NOT_FOUND, *it0);
                                            else if (it0 == it_tens->first)
                                                return std::make_tuple(Errors::ErrorCodes::UNITS_BEFORE_UND, QString());
                                        }
                                        else if (it0 == it_plus->first)
                                            return std::make_tuple(Errors::ErrorCodes::UNITS_BEFORE_UND, QString());
                                    }
                                    else if (it0 == it_units->first)
                                    {
                                        auto it2 = it + 1;
                                        if (it2 == input.end())
                                            return std::make_tuple(Errors::ErrorCodes::TENS_AFTER_UND, QString());
                                        else
                                        {
                                            auto it_units = maps::units.find(*it2);
                                            auto it_tens = maps::tens.find(*it2);
                                            auto it_plus = maps::tens_plus.find(*it2);

                                            if (it_units == maps::units.end())
                                            {
                                                if (it_plus == maps::tens_plus.end())
                                                {
                                                    if (it_tens == maps::tens.end())
                                                        return std::make_tuple(Errors::ErrorCodes::NOT_FOUND, *it2);
                                                    else if (it2 == it_tens->first)
                                                    {
                                                        if (*it2 == zehn || *it2 == hundert)
                                                            return std::make_tuple(Errors::ErrorCodes::TENS_AFTER_UND, QString());
                                                        else
                                                            continue;
                                                    }
                                                }
                                                else if (it2 == it_plus->first)
                                                    return std::make_tuple(Errors::ErrorCodes::TENS_AFTER_UND, QString());
                                            }
                                            else if (it2 == it_units->first)
                                                return std::make_tuple(Errors::ErrorCodes::TENS_AFTER_UND, QString());
                                        }
                                    }
                            }
                        }
                    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~если tens
                    else if (it == it_tens->first)
                    {
                        if (*it == hundert)
                        {
                            for (auto i = it + 1; i < input.end(); i++)
                            {
                                if (*i == hundert)
                                    return std::make_tuple(Errors::ErrorCodes::JUST_ONE_TIME, hundert);
                                else
                                    continue;
                            }
                            auto it2 = it + 1;
                            if (it2 == input.end())
                                return std::make_tuple(Errors::ErrorCodes::NO_ERROR, QString());
                            else
                            {
                                if (*it2 == hundert)
                                    return std::make_tuple(Errors::ErrorCodes::ONE_DIGIT_NUMBERS, QString());
                                else
                                {
                                    auto it_units = maps::units.find(*it2);
                                    auto it_tens = maps::tens.find(*it2);
                                    auto it_plus = maps::tens_plus.find(*it2);

                                    if (it_units == maps::units.end())
                                    {
                                        if (it_plus == maps::tens_plus.end())
                                        {
                                            if (it_tens == maps::tens.end())
                                            {
                                                if (*it2 != und)
                                                    return std::make_tuple(Errors::ErrorCodes::NOT_FOUND, *it2);
                                                else if (*it2 == und)
                                                    continue;
                                            }
                                            else if (it2 == it_tens->first)
                                                continue;
                                        }
                                        else if (it2 == it_plus->first)
                                            continue;
                                    }
                                    else if (it2 == it_units->first)
                                        continue;
                                }
                            }
                        }
                        else
                        {
                            auto it2 = it + 1;
                            if (it2 == input.end())
                                return std::make_tuple(Errors::ErrorCodes::NO_ERROR, QString());
                            else
                                return std::make_tuple(Errors::ErrorCodes::NO_ONE_AFTER_TENS, QString());
                        }
                    }
                }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~если tens_plus
                else if (it == it_plus->first)
                {
                    auto it2 = it + 1;
                    if (it2 == input.end())
                        return std::make_tuple(Errors::ErrorCodes::NO_ERROR, QString());
                    else
                        return std::make_tuple(Errors::ErrorCodes::NO_ONE_AFTER_TENS_PLUS, QString());
                }
            }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~если units
            else if (it == it_units->first)
            {
                auto it2 = it + 1;
                if (it2 == input.end())
                    return std::make_tuple(Errors::ErrorCodes::NO_ERROR, QString());
                else
                {
                    auto it_units = maps::units.find(*it2);
                    auto it_tens = maps::tens.find(*it2);
                    auto it_plus = maps::tens_plus.find(*it2);

                    if (it_units == maps::units.end())
                    {
                        if (it_plus == maps::tens_plus.end())
                        {
                            if (it_tens == maps::tens.end())
                            {
                                if (*it2 != und)
                                    return std::make_tuple(Errors::ErrorCodes::NOT_FOUND, *it2);
                                else if (*it2 == und)
                                    continue;
                            }
                            else if (it2 == it_tens->first)
                            {
                                if (*it2 == hundert)
                                    continue;
                                else
                                    return std::make_tuple(Errors::ErrorCodes::OTHERS_NEXT_TO_UNITS, QString());
                            }
                        }
                        else if (it2 == it_plus->first)
                            return std::make_tuple(Errors::ErrorCodes::OTHERS_NEXT_TO_UNITS, QString());
                    }
                    else if (it2 == it_units->first)
                        return std::make_tuple(Errors::ErrorCodes::ONE_DIGIT_NUMBERS, QString());
                }
            }
        }
    }

    return std::make_tuple(Errors::ErrorCodes::BULLSHIT, QString());
}


void Transform::show_error(int error_code, const QString &result)
{
    if (error_code == 4)
        QMessageBox::warning(0, QObject::tr("ОШИБКА!"), QObject::tr("Слово") + " " + result + " " + QObject::tr("не найдено!"), QMessageBox::Ok);

    else if (error_code == 2)
        QMessageBox::warning(0, QObject::tr("ОШИБКА!"), QObject::tr("Строка пуста! Введите строку."), QMessageBox::Ok);

    else if (error_code == 3)
        QMessageBox::warning(0, QObject::tr("ОШИБКА!"), QObject::tr("Два числа одного разряда не могут стоять друг за другом!"), QMessageBox::Ok);

    else if (error_code == 5)
        QMessageBox::warning(0, QObject::tr("ОШИБКА!"), QObject::tr("После числа из диапазона [1..9] НЕ может стоять число из диапазона [10...99]!"), QMessageBox::Ok);

    else if (error_code == 6)
        QMessageBox::warning(0, QObject::tr("ОШИБКА!"), QObject::tr("После десятков должно быть пусто!"), QMessageBox::Ok);

    else if (error_code == 7)
        QMessageBox::warning(0, QObject::tr("ОШИБКА!"), QObject::tr("После [11...19] должно быть пусто!"), QMessageBox::Ok);

    else if (error_code == 8)
        QMessageBox::warning(0, QObject::tr("ОШИБКА!"), QObject::tr("Перед und должно быть число в диапазоне [1...9]!"), QMessageBox::Ok);

    else if (error_code == 9)
        QMessageBox::warning(0, QObject::tr("ОШИБКА!"), QObject::tr("После und должны быть десятки (кроме 10)!"), QMessageBox::Ok);

    else if (error_code == 10)
        QMessageBox::warning(0, QObject::tr("ОШИБКА!"), QObject::tr("Слово") + " " + result + " " + QObject::tr("не может повторяться!"), QMessageBox::Ok);
}
