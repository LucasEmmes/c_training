#include <assert.h>
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char const *argv[]) {

    char * x = malloc(sizeof(char) * 4);

    x[3] = 12;
    assert(x[1][1] == 12);

    free(x);
}