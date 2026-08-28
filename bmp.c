#include "bmp.h"
#include "image.h"
#include <stdio.h>
#include <stdlib.h>

Image *load_bmp(FILE *bmp_file) {
    BMPHeader file_header;
    BMPInfoHeader info_header;
    uint32_t biSize;

    fread(&info_header, sizeof(BMPHeader), 1, bmp_file);

    // per ora supporto solo i bmp con infoheader da 40byte
    // quindi leggo separatamente bisize e vedo se posso leggere il file.
    // poi fseek torna indietro per leggere lo struct in una volta sola
    fread(&biSize, sizeof(uint32_t), 1, bmp_file);
    fseek(bmp_file, -4, SEEK_CUR);

    if (biSize==40) {
        fread(&info_header, sizeof(BMPInfoHeader), 1, bmp_file);
    }
    else {
        printf("BMP Info Header size is %d.\nFile currently not supported\n", biSize);
        return NULL;
    }


}
