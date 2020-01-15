#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVector>

#include "transform.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void error_nf(QString word);

private slots:

    void on_test_btn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
