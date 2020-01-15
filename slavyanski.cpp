#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "maps.h"

void MainWindow::slav (int &arab)
{
    int buf = 0;
    int buf1 = 0;
    auto it = maps::slava.find(arab);
    if (arab == it->first)
        ui->lineEdit_2->setText(it->second);
    else
    {
            buf = arab % 10;
            arab -= buf;
            auto it = maps::slava.find(arab);
            if (arab == it->first)
            {
                ui->lineEdit_2->insert(it->second);
                auto it = maps::slava.find(buf);
                if (it == maps::slava.end())
                    ui->lineEdit_2->insert("");
                else
                    ui->lineEdit_2->insert(it->second);
            }
            else
            {
                buf1 = arab % 100;
                arab -= buf1;
                auto it = maps::slava.find(arab);
                if (it == maps::slava.end())
                    ui->lineEdit_2->insert("");
                else
                {
                    ui->lineEdit_2->insert(it->second);
                    auto it = maps::slava.find(buf1);
                    if (it == maps::slava.end())
                        ui->lineEdit_2->insert("");
                    else
                    {
                        ui->lineEdit_2->insert(it->second);
                        auto it = maps::slava.find(buf);
                        if (it == maps::slava.end())
                            ui->lineEdit_2->insert("");
                        else
                            ui->lineEdit_2->insert(it->second);
                    }
                }
            }
        }
    }
