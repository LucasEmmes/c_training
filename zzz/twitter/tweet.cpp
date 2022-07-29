#include <stdio.h>
#include <ostream>
#include <iostream>
#include <string>

#include "tweet.h"
#include "user.h"
using namespace std;

extern int tweetCounter;

Tweet::Tweet(User* au, string nc) {
    // Increment counter
    tweetCounter += 1;
    // Apply id
    id = tweetCounter;
    // Apply content
    content = nc;
    // Apply author
    author = au;
}

Tweet::Tweet(User* au, string nc, Tweet* rp) {
    // Increment counter
    tweetCounter += 1;
    // Apply id
    id = tweetCounter;
    // Apply content
    content = nc;
    // Apply author
    author = au;
    // Add reply pointer
    replyTo = rp;
}

void Tweet::show() {
    cout
    <<"Tweet #"<<id<<" by @"<<author->getUsername()<<":\n";
    if (replyTo != NULL) {
        cout
        <<"Reply to tweet #"<<replyTo->id<<" by @"<<replyTo->author->getUsername();
    }
    cout
    <<"\n"<<content<<"\n"
    <<endl;
}

void Tweet::showThread() {
    if (replyTo == NULL) {
        cout << "Thread:" << endl;
    } else {
        replyTo->showThread();
        cout << "|" << endl;
    }
    cout << "@" << author->getUsername() << ":\n|   "
    << content << endl;
}