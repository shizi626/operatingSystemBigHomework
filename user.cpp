#include "user.h"
using namespace std;

User::User(string name,string psw):
    username(name),password(psw),isLogin(false)
{

}

bool User::login(string name,string psw){
    if(validateUser(name,psw)){
        isLogin=true;
        cout<<"login successfully!"<<endl;
        return true;
    } else {
        return false;
    }
}

bool User::validateUser(string name,string psw){
    if(username==name&&password==psw){
        return true;
    } else {
        return false;
    }
}

void User::logout(string name){
    if(isLogin){
        isLogin=false;
        cout<<"logout successfully"<<endl;
        return;
    }
    cout<<"you are not login!"<<endl;
}
