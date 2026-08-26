#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

FILE *read_file(char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Errore nell'apertura del file \n");
        return NULL;
    }
    return f;
}

char *get_file_extension(char *filename) {
    int name_len = strlen(filename);
    int extension_len = 0;
    int i = name_len-1;
    char x;

    for (x = filename[name_len-1]; x!='.'; i--) {
        x = filename[i];
        extension_len++;
    }

    // if extension_len is 0 no extension can be found
    if (extension_len == 0) return NULL;

    char *extension = malloc(sizeof(char)*extension_len);

    // if I use extension_len -1 here and in the malloc i can remove the '.'
    // at the beginning of the extension
    for(i=0; i<extension_len; i++) {
        extension[i] = filename[i+name_len-extension_len];
    }

    return extension;
}
