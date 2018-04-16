#ifndef CONFIG_H
#define CONFIG_H

// Gaussian blur parameters
struct GaussianBlurSettings {
    int blockSize;  // Gaussian kernel size
    double sigma;   // Sigma for Gaussian kernel
};

typedef struct GaussianBlurSettings GAUSSIAN_BLUR_SETTINGS;

#endif // CONFIG_H

