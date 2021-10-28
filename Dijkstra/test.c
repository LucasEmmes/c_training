#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{

    // char arr[] = {1,2,3};
    // char *a;
    // a = arr;

    // printf("%d", a[0]);
    
    char * a; 
    a = (char *) malloc(sizeof(char)*4);
    a[3] = 69;
    printf("%d", a[3]);
    

    return 0;
}
