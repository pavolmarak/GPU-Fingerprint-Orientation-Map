#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
    ui->plot->xAxis->setRange(0, 3000);
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

    // taking current image size from GUI
    int currWidth = ui->currentWidth->value();
    int currHeight = ui->currentHeight->value();

    // checking if O-Map block size is smaller than both image dimensions
    if(currHeight < ui->omapBlockSize->value() || currWidth < ui->omapBlockSize->value()){
        ui->log->append("<span style=\"color:red;\">O-Map blocksize must be equal or higher than any of the dimensions.</span><br>");
        return;
    }

    // clearing data vectors before plotting
    this->xdata.clear();
    this->timesCpu.clear();
    this->timesGpu.clear();

    // checking if there is at least one test to be performed
    if(ui->howManyIncrements->value() > 0){
        qDebug() << "Test time:" << QDateTime::currentDateTime().toString().toUpper();
        ui->log->append("<b>Test time:</b> " + QDateTime::currentDateTime().toString().toUpper());
    }

    // testing loop for increasing image size
    for(int cc = 0;cc<ui->howManyIncrements->value();cc++){
        // loading an image
        //imgMat = cv::imread("./db/88_2.tif",cv::IMREAD_GRAYSCALE);
        imgMat = cv::Mat(currHeight,currWidth,CV_8UC1);
        cv::transpose(imgMat,imgMat_transposed);
        af::array imgAf(imgMat.rows, imgMat.cols, imgMat_transposed.data);

        // CPU computation
        omap.setParams(imgMat,ui->omapBlockSize->value(),gbsBasic, gbsAdvanced);
        double accumCPU=0.0;
        for(int i=0;i<ui->numTests->value();i++){
            accumCPU += omap.computeBasicMap();
            qApp->processEvents();
        }

        // GPU computation
        omap_gpu.setParams(imgAf,ui->omapBlockSize->value(),gbsBasic,gbsAdvanced);
        // GPU warm-up
        omap_gpu.computeBasicMap(); // could be done better
        //omap_gpu.drawBasicMap();
        double accumGPU=0.0;
        for(int i=0;i<ui->numTests->value();i++){
            accumGPU += omap_gpu.computeBasicMap();
            qApp->processEvents();
        }

        // printing out
        qDebug() << "\nDimensions:" << currWidth << "x" << currHeight;
        qDebug() << "Time CPU (OpenCV):" << accumCPU/ui->numTests->value();
        qDebug() << "Time GPU (ArrayFire):" << accumGPU/ui->numTests->value();
        qDebug() << "CPU/GPU time ratio" << accumCPU/accumGPU;

        ui->log->append("\nDimensions: " + QString::number(currWidth) + " x " + QString::number(currHeight));
        ui->log->append("Time CPU (OpenCV): " + QString::number(accumCPU/ui->numTests->value()));
        ui->log->append("Time GPU (ArrayFire): " + QString::number(accumGPU/ui->numTests->value()));
        if((accumCPU/accumGPU) > 1.0){
             ui->log->append("CPU/<b style=\"background-color:rgb(0,100,0);color:rgb(255,255,255);\">GPU</b> time ratio: " + QString::number(accumCPU/accumGPU));
             ui->log->append("GPU is " + QString::number(accumCPU/accumGPU) + " times faster");
             qDebug() << "GPU is " << QString::number(accumCPU/accumGPU) << " times faster";
        }
        else{
            ui->log->append("<b style=\"background-color:rgb(0,100,0);color:rgb(255,255,255);\">CPU</b>/GPU time ratio: " + QString::number(accumCPU/accumGPU));
            ui->log->append("CPU is " + QString::number(accumGPU/accumCPU) + " times faster");
            qDebug() << "CPU is " << QString::number(accumGPU/accumCPU) << " times faster";
        }

        // update the plot
        this->xdata.push_back(currHeight);
        this->timesCpu.push_back(accumCPU/ui->numTests->value());
        this->timesGpu.push_back(accumGPU/ui->numTests->value());
        ui->plot->graph(0)->setData(this->xdata, this->timesCpu);
        ui->plot->graph(1)->setData(this->xdata, this->timesGpu);
        ui->plot->replot();

        // update the image size
        currWidth+=ui->increment->value();
        currHeight+=ui->increment->value();
    }

    // checking if there is at least one test to be performed
    if(ui->howManyIncrements->value() > 0){
        qDebug() << "\nTest finished:" << QDateTime::currentDateTime().toString().toUpper() << "\n..........\n\n";
        ui->log->append("\nTest finished: " + QDateTime::currentDateTime().toString().toUpper() + "\n..........\n\n");
    }
}

// function to show O-Map of selected image
void MainWindow::on_chooseFileVis_clicked()
{
    // create an instance of OMap_GPU
    OMap_GPU omapGPU;
    // create Gaussian blur settings
    GaussianBlurSettings gbsBasic{5,1.0}, gbsAdvanced{121,10.0};
    // path to image file user selected
    QString str = QFileDialog::getOpenFileName(this,"Choose image file",".","*.tif *.png *.bmp *.jpg");
    // load image to af::array

    try{
        af::array imgAf = af::loadImage(str.toStdString().c_str()).as(u8);
        qDebug() << "Image loaded successfully.";
        ui->log->append("\nImage loaded successfully.");
        qApp->processEvents();
        // set parameters for O-Map computation
        omapGPU.setParams(imgAf,ui->omapVisBlk->value(),gbsBasic,gbsAdvanced);
        // compute basic O-Map
        omapGPU.computeBasicMap();
        // draw and display map
        omapGPU.drawBasicMap();
    }
    catch(af::exception& ex){
        qDebug() << ex.what();
        ui->log->append(QString("\n.................\n") + ex.what());
    }

}
