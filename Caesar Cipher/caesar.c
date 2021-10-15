#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

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

char alphabet[32] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ', ',', '.', '!', '?', '\n'};
char shifted[32] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' ', ',', '.', '!', '?', '\n'};


int main(int argc, char const *argv[]) {

    // Open file
    FILE *fPointer;
    fPointer = fopen("cock.txt", "r");

    // Find end
    fseek(fPointer, 0L, SEEK_END);
    // Save length
    int input_length = ftell(fPointer);
    printf("Length: %d\n", input_length);
    // Go back to start
    rewind(fPointer);


    while (!feof(fPointer))
    {
        // count amount of characters manually
    }
    



    // alloc space for string
    char * text = malloc(sizeof(char) * input_length);
    // read
    for (int i = 0; i < input_length; i++)
    {
        text[i] = fgetc(fPointer);
    }
    
    int nl_characters = 0;
    for (int i = 0; i < input_length; i++)
    {
        if (text[i] == '\n')
        {
            nl_characters++;
        }
        
    }

    input_length = input_length - nl_characters;

    for (int i = 0; i < input_length; i++)
    {
        printf("%c", text[i]);
    }
    
    printf("_");
    


    // shift correct amount

    // apply shifted alphabet to text

    // save to output file

    fclose(fPointer);
    return 0;
}
