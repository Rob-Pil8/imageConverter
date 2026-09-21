#include "image.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

// returns -1 if x is not found in string
int count_chars_till_char_x(char* string, char x, int start_pos) {
    int counter = 0;

    for(int i=start_pos; i<(int)strlen(string) + start_pos; i++) {
        if(string[i] != x) {
            counter++;
        } else {
            return counter;
        }
    }

    return -1;
}


bool str_present_in_str_array(char *str, char *supported_formats) {
    bool supported = false;
    int i=0;
    char input_ext[strlen(str) +1];
    input_ext[strlen(str)] = '\0';

    for(int p=0; p<(int)strlen(str); p++) {
        input_ext[p] = str[p];
    }

    while(true) {

        if(supported_formats[i+1] == '\0') {
            break;
        }

        int ext_len = count_chars_till_char_x(supported_formats, '_', i);
        char ext_letters[ext_len+1];
        int equal_letters = 0;

        ext_letters[ext_len] = '\0';

        for(int j=i; j<ext_len + i; j++) {
            ext_letters[j-i] = supported_formats[j];
        }

        // I'll leave this commented out printf because it revealed a bug
        // the input extension contains the '.', so it is .bmp and not bmp
        // hence the ext_letters +1 and l=1 and [l-1] in the following if
        //printf("%d \n %d", (int)strlen(input_ext), (int)strlen(ext_letters));

        if(strlen(input_ext) == strlen(ext_letters)+1) {
            for(unsigned long l=1; l<strlen(input_ext)+1; l++) {
                if(tolower(input_ext[l]) == ext_letters[l-1]) {
                    equal_letters++;
                }
            }
        }

        if(equal_letters == (int)strlen(input_ext) && equal_letters != 0) {
            supported = true;
            break;
        }


        // if ext_len is 3, the second ext starts at the 4th position -> "bmp_ext2"
        i += ext_len +1;
    };

    //printf("%d \n", supported);
    return supported;
}
