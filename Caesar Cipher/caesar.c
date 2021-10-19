#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

char alphabet[64] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ', ',', '.', '!', '?', '\n', ':', ';', '-', '_', '\'', '"'};
char shifted_alphabet[64] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ', ',', '.', '!', '?', '\n', ':', ';', '-', '_', '\'', '"'};

void shift_alphabet(char alph[], char n) {

    // Allocate enough mempry to hold what is shifted out the left side
    char * temp = malloc(sizeof(char) * n);

    // Transfer left overflow
    for (char i = 0; i < n; i++)
    {
        temp[i] = alph[i];
    }

    // Shift characters left by a factor of n
    for (char i = 0; i < 64-n; i++)
    {
        alph[i] = alph[i+n];
    }

    // Put overflow back
    for (char i = 0; i < n; i++)
    {
        alph[64-n+i] = temp[i];
    }
    
    free(temp);
}

char translate_letter(char letter, char plain[], char shifted[]) {

    // Find index of letter in correct alphabet
    for (char i = 0; i < 64; i++)
    {
        if (plain[i] == letter) {
            return shifted[i];
        }
    }

    // If it wasn't found, simple return original letter
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
            operation = 0;
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

    // Shift correct amount
    shift_alphabet(shifted_alphabet, key);

    // Apply shifted alphabet to text
    if (operation) // Encoding
    {
        for (int i = 0; i < input_length; i++)
        {
            text[i] = translate_letter(text[i], alphabet, shifted_alphabet);
        }
    }
    else        // Decoding
    {
        for (int i = 0; i < input_length; i++)
        {
            text[i] = translate_letter(text[i], shifted_alphabet, alphabet);
        }
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
