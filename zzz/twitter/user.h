#ifndef USER_H
#define USER_H

#include <string>
#include <bits/stdc++.h>
#include "tweet.h"
using namespace std;

class Tweet;

class User {
    int id;
    string username;
    string password;
    list<Tweet*> userTweets;
    list<Tweet*> userLikes;
    list<Tweet*> userRetweets;

    public:
        User();
        User(string username, string password);
        string getUsername();
        list<Tweet*> getTweets();
        void info();
        Tweet* makeTweet(string content);

};

#endif
