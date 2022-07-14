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

string getUsername() {
    return username;
}

void User::info() {
    cout
    <<"User: @"<<username<<"\n"
    <<"PWD: "<<password<<"\n"
    <<endl;
}

Tweet User::makeTweet(string content) {
    Tweet t(this, content);
    return t;
}