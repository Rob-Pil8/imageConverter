#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "image.h"

// surely there are better ways to do this but it works well enough for a small project
// '_' means that a format has ended
// to check if a format is the last or not i check if the following character is '\0'
char *supported_formats = "bmp_";

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
        printf("Source extension not found. Filename must be at least 3 characters long. 'x.y' \n");
        return -1;
    }
    char *source_extension = get_file_extension(argv[1]);
    if (source_extension == NULL) {
        // *source_extension returns NULL if no extension is found
        printf("File extension not found \n");
        return -1;
    }

    printf("Detected source extension: %s\n", source_extension);

    // ctrl-c / ctrl-v for the target extension cuz i'm lazy ;)
    int target_name_lenght = strlen(argv[2]);
    if (target_name_lenght < 3) {
        // I need at least 2 characters to find the extension (. and a letter)
        // but since a file like ".p" is a hidden file it is unlikely to be an image
        // It could technically work with only 2 characters but I feel like it's better this way
        printf("Target extension not found. Filename must be at least 3 characters long. 'x.y' \n");
        return -1;
    }
    char *target_extension = get_file_extension(argv[2]);
    if (target_extension == NULL) {
        // *source_extension returns NULL if no extension is found
        printf("Target file extension not found \n");
        return -1;
    }

    printf("Detected target extension: %s\n", target_extension);

    //check if both the source and target extensions are supported

    bool source_ext_supported = true;
    bool target_ext_supported = true;
    if(str_present_in_str_array(source_extension, supported_formats) == false) {
        printf("Source extension not supported. \n");
        source_ext_supported = false;
    }

    if(str_present_in_str_array(target_extension, supported_formats) == false) {
        printf("Target extension not supported. \n");
        target_ext_supported = false;
    }

    if(source_ext_supported == false || target_ext_supported == false) return -1;

    return 0;
}

//TODOs
// 2) switch case to convert every known file format in the internal format (possibly in a separate function)
// 3) switch case to convert from the internal format into an output format (separate function)
