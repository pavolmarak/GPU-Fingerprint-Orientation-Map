#ifndef CONFIG_H
#define CONFIG_H

// nastavenia pre funkciu GaussianBlur, ktora sa pouziva na vyhladenie smerovej mapy
struct GaussianBlurSettings {
    int blockSize;  // velkost bloku pre vyhladenie smerovej mapy (cez bloky)
    double sigma;   // sigma pre vyhladenie smerovej mapy
};

typedef struct GaussianBlurSettings GAUSSIAN_BLUR_SETTINGS;

#endif // CONFIG_H
