#ifndef USER_H
#define USER_H

#include <string>
#include "tweet.h"
using namespace std;

class User {
    int id;
    string username;
    string password;
    public:
        User();
        User(string username, string password);
        string getUsername();
        void info();
        Tweet makeTweet(string content);
};

#endif
