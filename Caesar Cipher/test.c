#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <regex.h>

regex_t regex;
int reti;

int main(int argc, char const *argv[]) {
    printf("pain");
    reti = regcomp(&regex, "[A-Z]", 0);
    
    if (!reti) {
        printf("could not compile regex");
        exit(1);
    }

    reti = regexec(&regex, "A", 0, NULL, 0);
    if (!reti) {
        printf("MATCH :)");
    }
    else if (reti == REG_NOMATCH) {
        
        printf("NO MATCH :(");
    } else {
        printf("regex match failed");
    }


}
