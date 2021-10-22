#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>


char compress_letter(char letter) {
    if (letter == 10) {
        letter = 0;
    } else if (letter >= 32 && letter <= 126) {
        letter -= 31;
    } else {
        letter = 64;
    }

    return letter;
}

char decompress_letter(char letter) {
    if (letter == 0) {
        letter = 10;
    } else  {
        letter += 31;
    }

    return letter;
}

char shift_letter(char letter, char key) {
    printf("Raw: %c (%d) ", letter, letter);
    letter = compress_letter(letter);
    printf("Compressed: %d ", letter);
    letter = (letter + key)+96 % 96;
    printf("Shifted: %d ", letter);
    letter = decompress_letter(letter);
    printf("Decompressed: %c (%d)\n", letter, letter);
    return letter;
}


// TODO: take command line arguments
int main(int argc, char const *argv[]) {
    char key, operation;
    
    if (argc != 5) {
        printf("Usage: ./caesar [input filename] [output filename] [key (int)] [Operation en|de]\n");
    } else {
        key = (char) atoi(argv[3]) % 64;

        if (!strcmp("encode", argv[4])) {
            operation = 1;
        } else if (!strcmp("decode", argv[4])) {
            operation = -1;
        } else {
            printf("Unknown type of operation\nUsage: ./caesar [input filename] [output filename] [key (int)] [Operation en|de]\n");
            return 1;
        }
    }

    // Open file
    FILE *fPointer;
    fPointer = fopen(argv[1], "r");

    // Measure file to get accurate length, since fseek(fPointer, 0L, SEEK_END)
    // somehow counts '\n' as two chars
    int input_length = 0;
    char temp[1];
    while (!feof(fPointer))
    {
        fgets(temp, 2, fPointer);
        input_length++;
    }

    input_length--;
    rewind(fPointer);


    // Alloc space for string
    char * text = malloc(sizeof(char) * input_length);
    // Read in text
    for (int i = 0; i < input_length; i++)
    {
        text[i] = fgetc(fPointer);
    }
    fclose(fPointer);


    for (int i = 0; i < input_length; i++)
    {
        text[i] = shift_letter(text[i], key*operation);
    }



    // Save to output file
    FILE * fPoint_output;
    fopen_s(& fPoint_output, argv[2], "w");
    if (fPoint_output == NULL) {return 1;}
    fwrite(text, sizeof(char), input_length, fPoint_output);
    fclose(fPoint_output);

    free(text);
    return 0;
}
