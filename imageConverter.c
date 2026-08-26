#include <stdio.h>
#include <string.h>
#include "image.h"

// USAGE: ./imageConverter input.extension output.extension
int main(int argc, char **argv) {

    // check whether the right amount of command line arguments is passed
    if (argc < 3) {
        printf("Missing command-line argument(s) \n");
        printf("Usage: ./programName input.extension output.extension \n");
    }
    else if (argc > 3) {
        printf("Too many command-line arguments");
        printf("Usage: ./programName input.extension output.extension \n");
    }

    // for now I'll only support converting a single file
    FILE *f = read_file(argv[1]);

    // for now i'll just use the extension to recognize the file
    int source_name_lenght = strlen(argv[1]);
    if (source_name_lenght < 3) {
        // I need at least 2 characters to find the extension (. and a letter)
        // but since a file like ".p" is a hidden file it is unlikely to be an image
        // It could technically work with only 2 characters but I feel like it's better this way
        printf("Extension not found. Filename must be at least 3 characters long. 'x.y' \n");
        return -1;
    }
    char *source_extension = get_file_extension(argv[1]);
    if (source_extension == NULL) {
        // *source_extension returns NULL if no extension is found
        printf("File extension not found \n");
        return -1;
    }

    printf("Detected source extension: %s\n", source_extension);

    return 0;
}

//TODOs
// 1) check if bot the source and destination extensions are supported. If not show an error
// 2) switch case to convert every known file format in the internal format (possibly in a separate function)
// 3) switch case to convert from the internal format into an output format (separate function)
