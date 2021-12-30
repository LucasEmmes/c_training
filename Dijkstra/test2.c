#include <assert.h>
#include <stdio.h>
#include <string.h>

void foo(char * rebar) {

    char bar[10];

    strncpy(bar, rebar, sizeof(char)*5);

    for (int i = 0; i < 5; i++)
    {
        printf("%c", bar[i]);
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    // foo("Hello");
    assert(strcmp("Hello", "Hello") == 0);
}
