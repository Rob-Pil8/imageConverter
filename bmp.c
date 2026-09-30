#include "bmp.h"
#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

Image *load_bmp(FILE *bmp_file) {
    BMPHeader file_header;
    BMPInfoHeader info_header;
    uint32_t biSize;

    fread(&file_header, sizeof(BMPHeader), 1, bmp_file);

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

    if (info_header.biCompression != BI_RGB) {
        printf("BMP compresion not supported \nSorry for the inconvinience");
        return NULL;
    }

    if (info_header.biBitCount != 24) {
        fprintf(stderr, "Bit depth non supportato: %u bit per pixel\n", info_header.biBitCount);
        return NULL;
    }

    int total_pixels = info_header.biWidth * info_header.biHeight;

    Image *img = create_image(info_header.biWidth, info_header.biHeight);

    /* BMP uses this quad rbg struct
     * sembra che con il 24bit/pixel non abbia il rgbreserved
     * i'm kinda confused rn
     typedef struct tagRGBQUAD {
       BYTE rgbBlue;
       BYTE rgbGreen;
       BYTE rgbRed;
       BYTE rgbReserved;
     } RGBQUAD;
     */

    // dimensione in pixel di una singola riga
    int row_size_no_padding = info_header.biWidth * info_header.biBitCount/8;
    int row_size = ((row_size_no_padding + 3) / 4) * 4;



}
