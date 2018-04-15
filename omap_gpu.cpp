#include "omap_gpu.h"

#undef max

OMap_GPU::OMap_GPU(QObject *parent) : QObject(parent)
{

}


void OMap_GPU::setParams(af::array imgFingerprint_, int blockSize_, GAUSSIAN_BLUR_SETTINGS &gaussBlurBasic_, GAUSSIAN_BLUR_SETTINGS &gaussBlurAdvanced_)
{
    this->imgFingerprint = imgFingerprint_;
    this->blockSize = blockSize_;
    this->gaussBlurBasic = gaussBlurBasic_;
    this->gaussBlurAdvanced = gaussBlurAdvanced_;
}

double OMap_GPU::computeBasicMap()
{
    af::timer t;
    t.start();

    af::array Gx, Gy;
    int height, width;
    af::array Vx, Vy;
    height = floor(this->imgFingerprint.dims(0) / this->blockSize);
    width = floor(this->imgFingerprint.dims(1) / this->blockSize);
    int paddingX = this->imgFingerprint.dims(1) - width*this->blockSize;
    int paddingY = this->imgFingerprint.dims(0) - height*this->blockSize;

    // vypocet gradientov x a y
    af::sobel(Gx,Gy,this->imgFingerprint);

    // vypocet Vx,Vy a Theta
    af::array GxCut = Gx(af::seq(paddingY/2,height*this->blockSize+paddingY/2-1), af::seq(paddingX/2,width*this->blockSize+paddingX/2-1));
    af::array GyCut = Gy(af::seq(paddingY/2,height*this->blockSize+paddingY/2-1), af::seq(paddingX/2,width*this->blockSize+paddingX/2-1));

    GxCut = af::unwrap(GxCut, this->blockSize,this->blockSize,this->blockSize,this->blockSize);
    GyCut = af::unwrap(GyCut, this->blockSize,this->blockSize,this->blockSize,this->blockSize);

    Vx =  af::sum(2*GxCut*GyCut);
    Vy =  af::sum(af::pow(GxCut,2)-af::pow(GyCut,2));
    this->oMap_basic = 0.5* af::atan2(Vx.as(f32),Vy.as(f32));

    this->oMap_basic = af::moddims(this->oMap_basic,height,width);

    // vyhladenie smerovej mapy
    af::array sinTheta = af::sin(2*this->oMap_basic);
    af::array cosTheta = af::cos(2*this->oMap_basic);

    af::array gk = af::gaussianKernel(this->gaussBlurBasic.blockSize, this->gaussBlurBasic.blockSize, this->gaussBlurBasic.sigma, this->gaussBlurBasic.sigma);

    sinTheta = af::convolve(sinTheta, gk);
    cosTheta = af::convolve(cosTheta, gk);

    this->oMap_basic = 0.5* af::atan2(sinTheta, cosTheta);

    return t.stop();
}

void OMap_GPU::computeAdvancedMap()
{

}


void OMap_GPU::drawBasicMap()
{

    unsigned char* dataImg = this->imgFingerprint.T().host<unsigned char>();
    float* dataOmap = this->oMap_basic.T().host<float>();

    cv::Mat imgOriginalp(this->imgFingerprint.dims(0),this->imgFingerprint.dims(1),CV_8UC1,dataImg);
    cv::Mat OMap_basic(this->oMap_basic.dims(0),this->oMap_basic.dims(1),CV_32FC1,dataOmap);
    cv::Mat imgOMap_basic(this->imgFingerprint.dims(0),this->imgFingerprint.dims(1),CV_8UC3);

    // farebny obrazok smerovej mapy po vyhladeni
    cv::cvtColor(imgOriginalp, imgOMap_basic, CV_GRAY2RGB);

    int height = floor(imgOriginalp.rows/this->blockSize);
    int width = floor(imgOriginalp.cols/this->blockSize);
    int paddingX = imgOriginalp.cols - width*this->blockSize;
    int paddingY = imgOriginalp.rows - height*this->blockSize;
    int rowsMat = OMap_basic.rows;
    int colsMat = OMap_basic.cols;
    double row1, col1, row2, col2, row3, col3, direction;

    for (int y = 0; y<rowsMat; y++){
        for(int x =0; x<colsMat; x++){
            direction = OMap_basic.at<float>(y,x)+CV_PI/2;
            row1 = y*this->blockSize+this->blockSize/2+paddingY/2;
            col1 = x*this->blockSize+this->blockSize/2+paddingX/2;
            row2 = row1 - sin(direction)*this->blockSize/2;
            col2 = col1 - cos(direction)*this->blockSize/2;
            row3 = row1 + sin(direction)*this->blockSize/2;
            col3 = col1 + cos(direction)*this->blockSize/2;
            cv::Point endPoint(col2,row2);
            cv::Point endPoint2(col3, row3);
            cv::line(imgOMap_basic, endPoint, endPoint2, cv::Scalar(0,255,0),1,4,0);
        }
    }

    cv::imshow("O-Map",imgOMap_basic);
}
af::array OMap_GPU::getImgOMap_basic() const
{
    return imgOMap_basic;
}

af::array OMap_GPU::getOMap_advanced() const
{
    return oMap_advanced;
}

af::array OMap_GPU::getOMap_basic() const
{
    return oMap_basic;
}

void OMap_GPU::printDim(af::array & arr)
{
    qDebug() << arr.dims(0) << arr.dims(1) << arr.dims(2) << arr.dims(3);
}

void OMap_GPU::showImg(const af::array & afmat, const char* text)
{
    af::Window window(afmat.dims(0), afmat.dims(1), text);
    do{
        window.image(afmat);
    } while( !window.close() );
}
