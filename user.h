#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include <iostream>
#include <string>
using namespace std;
class User{
private:
    string username;
    string password;
    bool isLogin;

public:
    User():
        username("default"),password("123"),isLogin(false){};
    User(string,string);
    ~User(){};

    const string getUserName()const{return username;};
    const bool getIsLogin()const{return isLogin;};

    bool validateUser(string name,string psw);
    bool login(string name, string psw);
    void logout(string name);
};

#endif // USER_H_INCLUDED
