#ifndef TWEET_H
#define TWEET_H

#include <string>
#include "user.h"
using namespace std;

class Tweet {
    int id = 0;
    string content = "Empty tweet";
    User author;
    public:
        Tweet(User author, string newContent);
        void show();
};


#endif
