#include <stdio.h>
#include <string>
#include <ostream>
#include <iostream>

#include "tweet.h"
#include "user.h"
using namespace std;

int tweetCounter = 0;
int userCounter = 0;

int main() {
    User u("Lucas", "password");

    Tweet t(u, "Amogus");
    t.show();

    return 0;
}