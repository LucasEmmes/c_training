#include <stdio.h>
#include <ostream>
#include <iostream>
#include <string>

#include "user.h"
#include "tweet.h"
using namespace std;
extern int userCounter;

User::User(){}

User::User(string un, string pw) {
    // Increment counter
    userCounter += 1;
    // Apply id
    id = userCounter;
    // Apply username
    username = un;
    // Apply password
    password = pw;
}
string User::getUsername() {
    return username;
}

list<Tweet*> User::getTweets() {
    return userTweets;
};

void User::info() {
    cout
    <<"User: @"<<username<<"\n"
    <<"PWD: "<<password<<"\n"
    <<"Tweets: "<<userTweets.size()<<"\n"
    <<endl;
}

Tweet* User::makeTweet(string content) {
    Tweet* t = new Tweet(this, content);
    userTweets.push_back(t);
    return t;
}