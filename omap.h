#ifndef OMAP_H
#define OMAP_H

#include <QObject>
#include <QtMath>
#include <QDebug>
#include <QTime>
#include <QElapsedTimer>
#include <fstream>
#include "opencv2/opencv.hpp"
#include "config.h"

class OMap : public QObject
{
    Q_OBJECT
public:
    explicit OMap(QObject *parent = nullptr);
    void setParams(const cv::Mat &imgFingerprint_, int blockSize_, GAUSSIAN_BLUR_SETTINGS &gaussBlurBasic_, GAUSSIAN_BLUR_SETTINGS &gaussBlurAdvanced_);
    double computeBasicMap();
    double computeAdvancedMap();
    void drawBasicMap(const cv::Mat &imgOriginal);
    cv::Mat getImgOMap_basic() const;
    cv::Mat getOMap_advanced() const;
    cv::Mat getOMap_basic() const;

signals:

public slots:
private:
    cv::Mat imgFingerprint; // fingerprint image
    int blockSize; // O-Map block size
    GAUSSIAN_BLUR_SETTINGS gaussBlurBasic, gaussBlurAdvanced;
    cv::Mat oMap_basic; // basic smoothed O-Map, 1 direction for each block
    cv::Mat oMap_advanced; // advanced smoothed O-Map, 1 direction for each pixel
    cv::Mat imgOMap_basic; // basic O-map as image (advanced O-map cannot be displayed since each pixel has different direction)
};

#endif // OMAP_H
