#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVector>

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
    std::tuple<int, QString> error(QVector<QString> &input);
    void slav(int &arab);


private slots:

    void on_test_btn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
