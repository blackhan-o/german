#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <iostream>
#include <maps.h>
#include <algorithm>
#include <QMessageBox>
#include <iterator>
#include <QLineEdit>
#include <QVector>
#include <QtCore>
#include <sstream>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->test_btn->setText("Ok");
    ui->test_btn->setAutoDefault(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_test_btn_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();

    QString unit = ui->input->text();   
    QString word = 0;

    QVector<QString> input = QVector<QString>::fromList(unit.split(' ', QString::SkipEmptyParts));
// ~~~~~~~~~~~~~~~~~~~~~~~~~~ERRORS~~~~~~~~~~~~~~~~~~~~~~~~~~
//    QString errword = input[0];

    int error_value = 0;
    QString error_word;
    std::tie(error_value, error_word) = error(input);

    if (error_value == 4)
    {
        QMessageBox::warning(this, tr("ОШИБКА!"), tr("Слово") + " " + error_word + " " + tr("не найдено!"), QMessageBox::Ok);
    }
    else if (error_value == 2)
    {
        QMessageBox::warning(this, tr("ОШИБКА!"), tr("Строка пуста! Введите строку."), QMessageBox::Ok);
    }
    else if (error_value == 3)
    {
        QMessageBox::warning(this, tr("ОШИБКА!"), tr("Два числа одного разряда не могут стоять друг за другом!"), QMessageBox::Ok);
    }
    else if (error_value == 5)
    {
        QMessageBox::warning(this, tr("ОШИБКА!"), tr("После числа из диапазона [1..9] НЕ может стоять число из диапазона [10...99]!"), QMessageBox::Ok);
    }
    else if (error_value == 6)
    {
        QMessageBox::warning(this, tr("ОШИБКА!"), tr("После десятков должно быть пусто!"), QMessageBox::Ok);
    }
    else if (error_value == 7)
    {
        QMessageBox::warning(this, tr("ОШИБКА!"), tr("После [11...19] должно быть пусто!"), QMessageBox::Ok);
    }
    else if (error_value == 8)
    {
        QMessageBox::warning(this, tr("ОШИБКА!"), tr("Перед und должно быть число в диапазоне [1...9]!"), QMessageBox::Ok);
    }
    else if (error_value == 9)
    {
        QMessageBox::warning(this, tr("ОШИБКА!"), tr("После und должны быть десятки (кроме 10)!"), QMessageBox::Ok);
    }
    else if (error_value == 10)
    {
        QMessageBox::warning(this, tr("ОШИБКА!"), tr("Слово") + " " + error_word + " " + tr("не может повторяться!"), QMessageBox::Ok);
    }

    else if (error_value == 1)
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
                        ui->lineEdit->setText(QString::number(it_tens->second));
                        int arab = it_tens->second;
                        slav(arab);
                    }
                }
                else if (it_plus->second > 0)
                {
                    ui->lineEdit->setText(QString::number(it_plus->second));
                    int arab = it_plus->second;
                    slav(arab);
                }
            }
            else if (it_units->second > 0)
            {
                ui->lineEdit->setText(QString::number(it_units->second));
                int arab = it_units->second;
                slav(arab);
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
                        if (input[1] == it_tens->first && it_tens->first == "hundert")
                        {
                            ui->lineEdit->setText(QString::number(it_units->second * 100));
                            int arab = it_units->second * 100;
                            slav(arab);
                        }
                        else
                            error(input);
                    }
                }
            }
            else if (input[0] == it_tens->first)
            {
                if (it_tens->first == "hundert")
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
                                if (it_tens->first == "hundert")
                                    error(input);
                                else
                                {
                                    ui->lineEdit->setText(QString::number(it_tens->second + 100));
                                    int arab = it_tens->second + 100;
                                    slav(arab);
                                }
                            }
                        }
                        else if (it_plus->second > 0)
                        {
                            ui->lineEdit->setText(QString::number(it_plus->second + 100));
                            int arab = it_plus->second + 100;
                            slav(arab);
                        }
                    }
                    else if (it_units->second > 0)
                    {
                        ui->lineEdit->setText(QString::number(it_units->second + 100));
                        int arab = it_units->second + 100;
                        slav(arab);
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
                    if (input[1] == "und")
                    {
                        auto it_tens = maps::tens.find(input[2]);
                        if (it_tens == maps::tens.end())
                            error(input);
                        else
                        {
                            ui->lineEdit->setText(QString::number(it_tens->second + it_units->second));
                            int arab = it_tens->second + it_units->second;
                            slav(arab);
                        }
                    }
                    else
                        error(input);
                }
                else if (input[1] == it_tens->first && it_tens->first == "hundert")
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
                                if (it_tens->first == "hundert")
                                    error(input);
                                else
                                {
                                    ui->lineEdit->setText(QString::number(it_tens->second + sotni));
                                    int arab = it_tens->second + sotni;
                                    slav(arab);
                                }
                            }
                        }
                        else if (it_plus->second > 0)
                        {
                            ui->lineEdit->setText(QString::number(it_plus->second + sotni));
                            int arab = it_plus->second + sotni;
                            slav(arab);
                        }
                    }
                    else if (it_units->second > 0)
                    {
                        ui->lineEdit->setText(QString::number(it_units->second + sotni));
                        int arab = it_units->second + sotni;
                        slav(arab);
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
                    if (it_tens->first == "hundert")
                    {
                        auto it_units = maps::units.find(input[1]);

                        if (it_units == maps::units.end())
                            error(input);
                        else if (input[1] == it_units->first)
                        {
                            if (input[2] == "und")
                            {
                                auto it_tens = maps::tens.find(input[3]);
                                if (it_tens == maps::tens.end())
                                    error(input);
                                else
                                {
                                    if (it_tens->first == "hundert")
                                        error(input);
                                    else
                                    {
                                        ui->lineEdit->setText(QString::number(it_tens->second + it_units->second + 100));
                                        int arab = it_tens->second + it_units->second + 100;
                                        slav(arab);
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
                        if (it_tens->first == "hundert")
                        {
                            int sotni = it_units->second * 100;
                            auto it_units = maps::units.find(input[2]);

                            if (it_units == maps::units.end())
                                error(input);
                            else if (input[2] == it_units->first)
                            {
                                if (input[3] == "und")
                                {
                                    auto it_tens = maps::tens.find(input[4]);
                                    if (it_tens == maps::tens.end())
                                        error(input);
                                    else
                                    {
                                        if (it_tens->first == "hundert")
                                            error(input);
                                        else
                                        {
                                            ui->lineEdit->setText(QString::number(it_tens->second + it_units->second + sotni));
                                            int arab = it_tens->second + it_units->second + sotni;
                                            slav(arab);
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
}                   // zwei hundert acht zehn

