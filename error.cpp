#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "maps.h"

#include <QMessageBox>
#include <tuple>


//void MainWindow::error_nf(QString word)
//{
//    QMessageBox::warning(this, tr("ОШИБКА!"), tr("Слово") + " " + word + " " + tr("не найдено!"), QMessageBox::Ok);
//}


//return 1 -- OK
//return 2 -- Пустая строка
//return 3 -- Числа из одного разряда рядом
//return 4 -- Слова не существует!
//return 5 -- После числа [1..9] НЕ может стоять число [10...99]!
//return 6 -- Десятки должны быть последними!
//return 7 -- После [11...19] должно быть пусто!
//return 8 -- Перед und должно быть число в диапазоне [1...9]!
//return 9 -- После und должны быть десятки!
//return 10 -- hundert не может повторяться!


std::tuple<int, QString> MainWindow::error(QVector<QString> &input)
{
    for (auto it = input.begin(); it <= input.end(); it++)
    {
        if (it == input.end())
        {
            return std::make_tuple(2, QString());
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
                        if (*it != "und")
                        {
                            return std::make_tuple(4, *it);
                        }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~если und
                        else if (*it == "und")
                        {
                            for (auto i = it + 1; i < input.end(); i++)
                            {
                                if (*i == "und")
                                    return std::make_tuple(10, "und");
                                else
                                    continue;
                            }
                            if (it == input.begin())
                                return std::make_tuple(8, QString());
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
                                                return std::make_tuple(4, *it0);
                                            else if (it0 == it_tens->first)
                                                return std::make_tuple(8, QString());
                                        }
                                        else if (it0 == it_plus->first)
                                            return std::make_tuple(8, QString());
                                    }
                                    else if (it0 == it_units->first)
                                    {
                                        auto it2 = it + 1;
                                        if (it2 == input.end())
                                            return std::make_tuple(9, QString());
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
                                                        return std::make_tuple(4, *it2);
                                                    else if (it2 == it_tens->first)
                                                    {
                                                        if (*it2 == "zehn" || *it2 == "hundert")
                                                            return std::make_tuple(9, QString());
                                                        else
                                                            continue;
                                                    }
                                                }
                                                else if (it2 == it_plus->first)
                                                    return std::make_tuple(9, QString());
                                            }
                                            else if (it2 == it_units->first)
                                                return std::make_tuple(9, QString());
                                        }
                                    }
                            }
                        }
                    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~если tens
                    else if (it == it_tens->first)
                    {
                        if (*it == "hundert")
                        {
                            for (auto i = it + 1; i < input.end(); i++)
                            {
                                if (*i == "hundert")
                                    return std::make_tuple(10, "hundert");
                                else
                                    continue;
                            }
                            auto it2 = it + 1;
                            if (it2 == input.end())
                                return std::make_tuple(1, QString());
                            else
                            {
                                if (*it2 == "hundert")
                                    return std::make_tuple(3, QString());
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
                                                if (*it2 != "und")
                                                    return std::make_tuple(4, *it2);
                                                else if (*it2 == "und")
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
                                return std::make_tuple(1, QString());
                            else
                                return std::make_tuple(6, QString());
                        }
                    }
                }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~если tens_plus
                else if (it == it_plus->first)
                {
                    auto it2 = it + 1;
                    if (it2 == input.end())
                        return std::make_tuple(1, QString());
                    else
                        return std::make_tuple(7, QString());
                }
            }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~если units
            else if (it == it_units->first)
            {
                auto it2 = it + 1;
                if (it2 == input.end())
                    return std::make_tuple(1, QString());
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
                                if (*it2 != "und")
                                    return std::make_tuple(4, *it2);
                                else if (*it2 == "und")
                                    continue;
                            }
                            else if (it2 == it_tens->first)
                            {
                                if (*it2 == "hundert")
                                    continue;
                                else
                                    return std::make_tuple(5, QString());
                            }
                        }
                        else if (it2 == it_plus->first)
                            return std::make_tuple(5, QString());
                    }
                    else if (it2 == it_units->first)
                        return std::make_tuple(3, QString());
                }
            }
        }
    }
}

//void MainWindow::error_nf(QString word)
//{
//    QMessageBox::warning(this, tr("ОШИБКА!"), tr("Слово") + " " + word + " " + tr("не найдено!"), QMessageBox::Ok);
//}

//void MainWindow::error()
//{
//    QMessageBox errorMessage;
//    errorMessage.critical(0, "Ошибка!", "Ключ не найден!");
//    errorMessage.setFixedSize(500, 200);
//}
