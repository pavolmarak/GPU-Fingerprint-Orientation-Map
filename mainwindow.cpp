#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //hello

    // inits
    this->dims_start = 50;
    this->dims_max = 3000;
    this->numTests = 50;
    this->blockSize = 13;

    // custom plot
    ui->plot->addGraph(); // CPU
    ui->plot->addGraph(); // GPU
    ui->plot->graph(0)->setName("CPU");
    ui->plot->graph(1)->setName("GPU");
    ui->plot->graph(0)->setPen(QPen(QBrush(Qt::blue),3));
    ui->plot->graph(1)->setPen(QPen(QBrush(Qt::red),3));
    ui->plot->graph(0)->setData(this->xdata, this->timesCpu);
    ui->plot->graph(1)->setData(this->xdata, this->timesGpu);
    ui->plot->xAxis->setLabel("Image size");
    ui->plot->yAxis->setLabel("Average Time [s]");
    ui->plot->xAxis->setRange(this->dims_start, this->dims_max);
    ui->plot->yAxis->setRange(0, 0.01);
    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->plot->legend->setVisible(true);
    ui->plot->xAxis2->setVisible(true);
    ui->plot->xAxis2->setTickLabels(true);
    ui->plot->yAxis2->setVisible(true);
    ui->plot->yAxis2->setTickLabels(true);
    ui->plot->replot();
    qApp->processEvents();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_runTestBTN_clicked()
{
    // declarations
    GaussianBlurSettings gbsBasic{5,1.0}, gbsAdvanced{121,10.0};
    cv::Mat imgMat, imgMat_transposed;
    OMap omap;
    OMap_GPU omap_gpu;

    // testovanie pre rozne rozmery
    for(int cc = this->dims_start;cc<=this->dims_max;cc+=50){
        qDebug() << "Dimensions:" << cc << "x" << cc;
        // loading an image
        // imgMat = cv::imread("./db/94_3.tif",cv::IMREAD_GRAYSCALE);
        imgMat = cv::Mat(cc,cc,CV_8UC1);
        cv::transpose(imgMat,imgMat_transposed);
        af::array imgAf(imgMat.rows, imgMat.cols, imgMat_transposed.data);

        // CPU computation
        omap.setParams(imgMat,this->blockSize,gbsBasic, gbsAdvanced);

        double accumCPU=0.0;
        for(int i=0;i<this->numTests;i++){
            accumCPU += omap.computeBasicMap();
        }
        qDebug() << "Time CPU:" << accumCPU/this->numTests;

        // GPU computation
        omap_gpu.setParams(imgAf,this->blockSize,gbsBasic,gbsAdvanced);
        omap_gpu.computeBasicMap(); // warm-up
        //omap_gpu.drawBasicMap();
        double accumGPU=0.0;
        for(int i=0;i<this->numTests;i++){
            accumGPU += omap_gpu.computeBasicMap();
        }
        qDebug() << "Time GPU:" << accumGPU/this->numTests;

        qDebug() << "CPU/GPU time ratio" << accumCPU/accumGPU;

        // update the plot
        this->xdata.push_back(cc);
        this->timesCpu.push_back(accumCPU/this->numTests);
        this->timesGpu.push_back(accumGPU/this->numTests);
        ui->plot->graph(0)->setData(this->xdata, this->timesCpu);
        ui->plot->graph(1)->setData(this->xdata, this->timesGpu);
        ui->plot->replot();
    }
}
