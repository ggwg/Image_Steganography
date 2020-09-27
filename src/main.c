#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/encode.h"
#include "../inc/decode.h"

int main(int argc, char **argv) {
    if (argc < 2 || argc > 9) {
        perror("Invalid argument length\n");
        return EXIT_FAILURE;
    }
    // parses the arguments and flags from terminal
    char is_encode = 0;
    char is_decode = 0;

    // Initializes default password to be NULL;
    char *password = "\0";

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0) {
            is_encode = 1;
            break;
        } else if (strcmp(argv[i], "-d") == 0) {
            is_decode = 1;
            break;
        }
    }
    if (is_encode) {
        char *BMP_PATH;
        char *INP_PATH;
        char *OUT_PATH;
        // parses paths of files
        for (int i = 0; i < argc; i++) {
            if (strcmp(argv[i], "-p") == 0) {
                password = argv[i + 1];
            }
            if (strcmp(argv[i], "-i") == 0) {
                if (argc > i + 2) {
                    if (strcmp(strrchr(argv[i + 1], '.') + 1, "bmp") == 0) {
                        BMP_PATH = argv[i + 1];
                        INP_PATH = argv[i + 2];
                    } else {
                        perror("First input file must be of format .bmp");
                        return EXIT_FAILURE;
                    }
                } else {
                    perror("Input argument missing after -i flag");
                    return EXIT_FAILURE;
                }
            } else if (strcmp(argv[i], "-o") == 0) {
                if (argc > i + 1) {
                    OUT_PATH = argv[i + 1];
                } else {
                    perror("No output file argument given");
                    return EXIT_FAILURE;
                }
            }
        }
        return encode_BMP(BMP_PATH, INP_PATH, OUT_PATH, password);
    } else if (is_decode) {
        char *BMP_PATH;
        for (int i = 0; i < argc; i++) {
            if (strcmp(argv[i], "-p") == 0) {
                password = argv[i + 1];
            }
            if (strcmp(argv[i], "-i") == 0) {
                if (argc > i + 1) {
                    BMP_PATH = argv[i + 1];
                } else {
                    perror("No input file argument given");
                    return EXIT_FAILURE;
                }
            }
        }
        return decode_BMP(BMP_PATH, password);
    } else {
        perror("Invalid flags");
        return EXIT_FAILURE;
    }

}
