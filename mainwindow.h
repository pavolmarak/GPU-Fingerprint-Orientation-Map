#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

#include "opencv2/opencv.hpp"
#include "arrayfire.h"
#include "omap.h"
#include "omap_gpu.h"
#include "qcustomplot.h"

#define DB "db"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:


    void on_runTestBTN_clicked();

private:
    Ui::MainWindow *ui;
    QImage img;
    QVector<double> xdata, timesCpu, timesGpu;
};

#endif // MAINWINDOW_H
