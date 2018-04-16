#ifndef OMAP_GPU_H
#define OMAP_GPU_H

#include <QObject>
#include <QDebug>

#include "opencv2/opencv.hpp"
#include "arrayfire.h"
#include "config.h"

class OMap_GPU : public QObject
{
    Q_OBJECT
public:
    explicit OMap_GPU(QObject *parent = nullptr);
    void setParams(af::array imgFingerprint_, int blockSize_, GAUSSIAN_BLUR_SETTINGS &gaussBlurBasic_, GAUSSIAN_BLUR_SETTINGS &gaussBlurAdvanced_);
    double computeBasicMap();
    void computeAdvancedMap();
    void drawBasicMap();
    af::array getImgOMap_basic() const;
    af::array getOMap_advanced() const;
    af::array getOMap_basic() const;
    void printDim(af::array&);
    void showImg(const af::array&, const char*);

signals:

public slots:
private:
    af::array imgFingerprint; // fingerprint image
    int blockSize; // O-Map block size
    GAUSSIAN_BLUR_SETTINGS gaussBlurBasic, gaussBlurAdvanced;
    af::array oMap_basic;  // basic smoothed O-Map, 1 direction for each block
    af::array oMap_advanced; // advanced smoothed O-Map, 1 direction for each pixel
    af::array imgOMap_basic; // basic O-map as image (advanced O-map cannot be displayed since each pixel has different direction)
};

#endif // OMAP_GPU_H
