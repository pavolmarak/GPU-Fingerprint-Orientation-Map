#include "omap_gpu.h"

#undef max

OMap_GPU::OMap_GPU(QObject *parent) : QObject(parent)
{

}

// function to set parameters of O-Map computation
void OMap_GPU::setParams(af::array imgFingerprint_, int blockSize_, GAUSSIAN_BLUR_SETTINGS &gaussBlurBasic_, GAUSSIAN_BLUR_SETTINGS &gaussBlurAdvanced_)
{
    this->imgFingerprint = imgFingerprint_;
    this->blockSize = blockSize_;
    this->gaussBlurBasic = gaussBlurBasic_;
    this->gaussBlurAdvanced = gaussBlurAdvanced_;
}

// function to compute O-map on GPU
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

    // computing gradients Gx and Gy
    af::sobel(Gx,Gy,this->imgFingerprint);

    // computing O-Map
    af::array GxCut = Gx(af::seq(paddingY/2,height*this->blockSize+paddingY/2-1), af::seq(paddingX/2,width*this->blockSize+paddingX/2-1));
    af::array GyCut = Gy(af::seq(paddingY/2,height*this->blockSize+paddingY/2-1), af::seq(paddingX/2,width*this->blockSize+paddingX/2-1));

    GxCut = af::unwrap(GxCut, this->blockSize,this->blockSize,this->blockSize,this->blockSize);
    GyCut = af::unwrap(GyCut, this->blockSize,this->blockSize,this->blockSize,this->blockSize);

    Vx =  af::sum(2*GxCut*GyCut);
    Vy =  af::sum(af::pow(GxCut,2)-af::pow(GyCut,2));
    this->oMap_basic = 0.5* af::atan2(Vx.as(f32),Vy.as(f32));

    this->oMap_basic = af::moddims(this->oMap_basic,height,width);

    // smoothing the O-Map
    af::array sinTheta = af::sin(2*this->oMap_basic);
    af::array cosTheta = af::cos(2*this->oMap_basic);

    af::array gk = af::gaussianKernel(this->gaussBlurBasic.blockSize, this->gaussBlurBasic.blockSize, this->gaussBlurBasic.sigma, this->gaussBlurBasic.sigma);

    sinTheta = af::convolve(sinTheta, gk);
    cosTheta = af::convolve(cosTheta, gk);

    this->oMap_basic = 0.5* af::atan2(sinTheta, cosTheta);

    // return time elapsed
    return t.stop();
}

// function to compute advanced (expanded) O-Map
double OMap_GPU::computeAdvancedMap()
{
    af::timer t;
    t.start();

    // compute the basic O-Map first
    this->computeBasicMap();

    // basic O-Map expansion
    this->oMap_advanced = af::moddims(this->oMap_basic,1,this->oMap_basic.dims(0)*this->oMap_basic.dims(1));
    this->oMap_advanced = af::tile(this->oMap_advanced,this->blockSize*this->blockSize);
    this->oMap_advanced = af::wrap(this->oMap_advanced,
                                   this->oMap_basic.dims(0)*this->blockSize,
                                   this->oMap_basic.dims(1)*this->blockSize,
                                   this->blockSize,
                                   this->blockSize,
                                   this->blockSize,
                                   this->blockSize);

    // smoothing the expanded O-Map
    af::array sinTheta = af::sin(2*this->oMap_advanced);
    af::array cosTheta = af::cos(2*this->oMap_advanced);
    af::array gk = af::gaussianKernel(this->gaussBlurAdvanced.blockSize,
                                      this->gaussBlurAdvanced.blockSize,
                                      this->gaussBlurAdvanced.sigma,
                                      this->gaussBlurAdvanced.sigma);

    sinTheta = af::convolve(sinTheta, gk);
    cosTheta = af::convolve(cosTheta, gk);

    this->oMap_advanced = 0.5* af::atan2(sinTheta, cosTheta);

    // return time elapsed
    return t.stop();
}

// function to draw basic O-Map on top of the original image
// the resulting image is stored in local variable 'basicOmapImage'
void OMap_GPU::drawBasicMap()
{
    // fingeprint image is transferred from VRAM to RAM
    unsigned char* dataImg = this->imgFingerprint.T().host<unsigned char>();
    // basic O-Map is transferred from VRAM to RAM
    float* dataOmap = this->oMap_basic.T().host<float>();

    // creating original image as cv::Mat
    cv::Mat imgOriginalp(this->imgFingerprint.dims(0),this->imgFingerprint.dims(1),CV_8UC1,dataImg);
    // creating basic O-Map as cv::Mat
    cv::Mat OMap_basic(this->oMap_basic.dims(0),this->oMap_basic.dims(1),CV_32FC1,dataOmap);
    // creating empty basic O-Map image
    cv::Mat basicOmapImage(this->imgFingerprint.dims(0),this->imgFingerprint.dims(1),CV_8UC3);

    // basic O-Map image has the original fingerprint image as the bottom layer
    cv::cvtColor(imgOriginalp, basicOmapImage, CV_GRAY2RGB);

    int height = floor(imgOriginalp.rows/this->blockSize);
    int width = floor(imgOriginalp.cols/this->blockSize);
    int paddingX = imgOriginalp.cols - width*this->blockSize;
    int paddingY = imgOriginalp.rows - height*this->blockSize;
    int rowsMat = OMap_basic.rows;
    int colsMat = OMap_basic.cols;
    double row1, col1, row2, col2, row3, col3, direction;

    // draw vector arrows on top of the fingerprint image
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
            cv::line(basicOmapImage, endPoint, endPoint2, cv::Scalar(0,255,0),1,4,0);
        }
    }

    // display the resulting basic O-Map image
    cv::imshow("O-Map",basicOmapImage);
}

// function to get basic O-Map image
// right now it returns an empty matrix
af::array OMap_GPU::getImgOMap_basic() const
{
    return imgOMap_basic;
}

// function to get advanced (expanded) O-Map
af::array OMap_GPU::getOMap_advanced() const
{
    return oMap_advanced;
}

// function to get basic O-Map
af::array OMap_GPU::getOMap_basic() const
{
    return oMap_basic;
}

// helper function to display input af::array dimensions
void OMap_GPU::printDim(af::array & arr)
{
    qDebug() << arr.dims(0) << arr.dims(1) << arr.dims(2) << arr.dims(3);
}

// helper function to display af::array image
void OMap_GPU::showImg(const af::array & afmat, const char* text)
{
    af::Window window(afmat.dims(0), afmat.dims(1), text);
    do{
        window.image(afmat);
    } while( !window.close() );
}
