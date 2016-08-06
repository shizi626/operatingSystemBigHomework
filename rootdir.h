#ifndef ROOTDIR_H_INCLUDED
#define ROOTDIR_H_INCLUDED

#include <iostream>
#include <bitset>
#include "user.h"
#include "mynode.h"
#include "userdir.h"

using namespace std;

class Rootdir{
    const static int nodeNumber;
private:
    User rootuser;
    string address;

    int nodeNow;

    enum{dirNumber=50};
    Mynode nodeList[dirNumber];
    Userdir dirList[dirNumber];

public:
    Rootdir();

    const string getRootAddr()const{return address;}

    void rootLogin(string name,string psw);
    void rootLogout(){rootuser.logout("/");}

    int getDirBlock(string dirname);
    bool isUnique(string dirname);
    bool createDir(string username,string userpsw="123");
    bool deleteDir(string username);

    void listDir();

    //operating file in userdir
    bool dirLogin(string dirname,string dirpsw="123");
    void dirLogout(string dirname);
    int openFile(string dirname,string filename);
    string readFile(string dirname,int fileBlock);
    void writeFile(string dirname,int fileBlock,string content);
    bool createFile(string dirname,string filename,bitset<4> proc=bitset<4>(string("1100")),
        string content="hello world!",string author="");
    bool deleteFile(string dirname,string filename);
    void listDirFile(string dirname);
};

#endif // ROOTDIR_H_INCLUDED
