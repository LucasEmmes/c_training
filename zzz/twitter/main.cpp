#include <stdio.h>
#include <string>
#include <ostream>
#include <iostream>

#include "tweet.h"
#include "user.h"
using namespace std;

// g++ user.cpp -c && g++ tweet.cpp -c && g++ main.cpp -c && g++ main.o tweet.o user.o -o twitter && ./twitter

int tweetCounter = 0;
int userCounter = 0;

int main() {
    User u("Lucas", "password");
    Tweet* t = u.makeTweet("Anime is cirnke (am weeb)");
    t->show();
    u.info();
    return 0;
}