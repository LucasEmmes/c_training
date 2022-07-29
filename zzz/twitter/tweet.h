#ifndef TWEET_H
#define TWEET_H

#include <string>
#include "user.h"
using namespace std;

class User;

class Tweet {
    int id = 0;
    string content = "Empty tweet";
    User* author;
    Tweet* replyTo = NULL;
    public:
        Tweet(User* author, string newContent);
        Tweet(User* author, string newContent, Tweet* replyTo);
        void show();
        void showThread();
};


#endif
