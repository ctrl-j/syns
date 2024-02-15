#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "sound.h"


int main(int argc, char** argv) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char* FILENAME = argv[1];
    char* DATA = "test";
    NSF_HEADER* HEADER = malloc(sizeof(NSF_HEADER));

    int WRITE_STATUS = WRITE_NSF_FILE(FILENAME, &HEADER, DATA);
    if (WRITE_STATUS == 1) {
        printf("Error writing NSF file: %d\n", WRITE_STATUS);
        return EXIT_FAILURE;
    }
}

