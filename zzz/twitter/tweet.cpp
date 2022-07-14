#include <stdio.h>
#include <ostream>
#include <iostream>
#include <string>

#include "tweet.h"
#include "user.h"
using namespace std;

extern int tweetCounter;

Tweet::Tweet(User au, string nc) {
    // Increment counter
    tweetCounter += 1;
    // Apply id
    id = tweetCounter;
    // Apply content
    content = nc;
    // Apply author
    author = au;
}

void Tweet::show() {
    cout
    <<"Tweet #"<<id<<" by @"<<author.getUsername()<<":\n"
    <<content<<"\n"
    <<endl;
}