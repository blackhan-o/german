#include <QMessageBox>
#include <QLineEdit>
#include <QVector>
#include <QtCore>

#include <iterator>
#include <sstream>
#include <algorithm>
#include <iostream>

#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "transform.h"
#include "maps.h"


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
    ui->ArabNum->clear();
    ui->SlavNum->clear();

    QString unit = ui->input->text();

    Transform transform_obj;

    QString result;
    QString result1;
    int error_value = 0;

    std::tie(error_value, result) = transform_obj.ger_to_arab(unit);

    transform_obj.show_error(error_value, result);

    ui->ArabNum->setText(result);
    QString arab = result;

    std::tie(error_value, result1) = transform_obj.arab_to_slav(arab.toInt());
    ui->SlavNum->insert(result1);
}


