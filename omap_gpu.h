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
    af::array imgFingerprint; // obrazok odtlacku
    int blockSize; // velkost bloku pre smerovu mapu
    GAUSSIAN_BLUR_SETTINGS gaussBlurBasic, gaussBlurAdvanced;
    af::array oMap_basic; // BASIC smerova mapa (vyhladena, jeden smer pre cely blok)
    af::array oMap_advanced; // ADVANCED smerova mapa (vyhladena, kazdy pixel ma svoj smer)
    af::array imgOMap_basic; // obrazok BASIC smerovej mapy (ADVANCED mapa sa neda zobrazit, lebo kazdy pixel ma iny smer)


};

#endif // OMAP_GPU_H
