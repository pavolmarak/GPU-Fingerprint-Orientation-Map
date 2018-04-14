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
    void setParams(const cv::Mat &imgFingerprint_, int &blockSize_, GAUSSIAN_BLUR_SETTINGS &gaussBlurBasic_, GAUSSIAN_BLUR_SETTINGS &gaussBlurAdvanced_);
    double computeBasicMap();
    void computeAdvancedMap();
    void drawBasicMap(const cv::Mat &imgOriginal);
    cv::Mat getImgOMap_basic() const;
    cv::Mat getOMap_advanced() const;
    cv::Mat getOMap_basic() const;


signals:

public slots:
private:
    cv::Mat imgFingerprint; // obrazok odtlacku
    int blockSize; // velkost bloku pre smerovu mapu
    GAUSSIAN_BLUR_SETTINGS gaussBlurBasic, gaussBlurAdvanced;
    cv::Mat oMap_basic; // BASIC smerova mapa (vyhladena, jeden smer pre cely blok)
    cv::Mat oMap_advanced; // ADVANCED smerova mapa (vyhladena, kazdy pixel ma svoj smer)
    cv::Mat imgOMap_basic; // obrazok BASIC smerovej mapy (ADVANCED mapa sa neda zobrazit, lebo kazdy pixel ma iny smer)
};

#endif // OMAP_H
