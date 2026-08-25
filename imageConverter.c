#include <stdio.h>
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

    return 0;
}
