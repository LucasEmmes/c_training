#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

char alphabet[32] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ', ',', '.', '!', '?', '\n'};
char shifted_alphabet[32] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ', ',', '.', '!', '?', '\n'};

void shift_alphabet(char alph[], char n) {

    // Allocate enough mempry to hold what is shifted out the left side
    char * temp = malloc(sizeof(char) * n);

    // Transfer left overflow
    for (char i = 0; i < n; i++)
    {
        temp[i] = alph[i];
    }

    // Shift characters left by a factor of n
    for (char i = 0; i < 32-n; i++)
    {
        alph[i] = alph[i+n];
    }

    // Put overflow back
    for (char i = 0; i < n; i++)
    {
        alph[32-n+i] = temp[i];
    }
    
    free(temp);
}

char translate_letter(char letter) {

    // Find index of letter in correct alphabet
    char index = 0;
    while (alphabet[index] != letter)
    {
        index ++;
    }
    
    return shifted_alphabet[index];

}


// TODO: take command line arguments
// TODO: enable encryption and decryption
// TODO: write output to file
int main(int argc, char const *argv[]) {

    char key = 5;

    // Open file
    FILE *fPointer;
    fPointer = fopen("cock.txt", "r");

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
    char char_check;
    // Read file again, transfer to text
    for (int i = 0; i < input_length; i++)
    {
        char_check = fgetc(fPointer);
        if ((char_check >= 65 && char_check <= 90) || char_check == 32 || char_check == 44 || char_check == 46 || char_check == 33 || char_check == 63 || char_check == 10) {
            // valid
        } else if (char_check >= 97 && char_check <= 122) {
            // lowercase character
            char_check = char_check - 32;
        } else {
            // invalid character, insert '?'
            char_check = 63;
        }

        text[i] = char_check;
    }

    // Print text (for debug)
    for (int i = 0; i < input_length; i++)
    {
        printf("%c", text[i]);
    }
    printf("\n\n");


    // Shift correct amount
    shift_alphabet(shifted_alphabet, key);

    // apply shifted alphabet to text
    for (int i = 0; i < input_length; i++)
    {
        text[i] = translate_letter(text[i]);
    }
    
    printf("_");
    // Print text (for debug)
    for (int i = 0; i < input_length; i++)
    {
        printf("%c", text[i]);
    }
    printf("_");

    // save to output file



    // // Find end
    // fseek(fPointer, 0L, SEEK_END);
    // // Save length
    // int input_length1 = ftell(fPointer);
    // printf("Length 1: %d\n", input_length1);
    // // Go back to start

    

    free(text);
    fclose(fPointer);
    return 0;
}
