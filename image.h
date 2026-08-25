#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>
#include <stdlib.h>

// internamente tutte le immagini saranno con canali 16bit, tanto il risparmio di memoria non è necessario
// lavorando su singole immagini con hardware moderno
typedef struct {
    uint16_t r, g, b;
} Pixel;

// per ora non preservo altri metadati
typedef struct {
    int width, height;
    Pixel *pixels;
} Image;

Image *create_image(int width, int height);
void free_image(Image **img);
Pixel *image_at(Image *img, int x, int y);

#endif
