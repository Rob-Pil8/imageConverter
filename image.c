#include "image.h"
#include <stdlib.h>

Image *create_image(int width, int height) {

    Image *img = malloc(sizeof(Image));
    if (img == NULL) return NULL;

    img->pixels = malloc(sizeof(Pixel) * width * height);
    if (img->pixels == NULL) {
        free(img);
        return NULL;
    }

    img->width = width;
    img->height = height;

    return img;
}

void free_image(Image **img) {
    if (img == NULL || *img == NULL) return;
    free((*img)->pixels);
    free(*img);
    *img = NULL;
}

Pixel *image_at(Image *img, int x, int y) {
    if (x >= img->width || y >= img->height || x<0 || y<0) return NULL;

    int index = ((img->width) * y ) + x;
    return &img->pixels[index];
}
