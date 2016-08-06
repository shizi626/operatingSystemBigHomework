#ifndef USERDIR_H_INCLUDED
#define USERDIR_H_INCLUDED

#include <string>
#include <bitset>

#include "myfile.h"
#include "user.h"
#include "mynode.h"

using namespace std;

class Userdir{
private:
    User subuser;
    string address;

    int nodeNow;
    int blockNo;
    enum{fileNumber=50};
    Mynode nodeList[fileNumber];
    Myfile fileList[fileNumber];

public:
    Userdir();

    // address is the root path plus the username
    // but dirName is the same as username
    Userdir(string username,string userpsw,int block);

    const string getDirName()const{return subuser.getUserName();}
    const string getDirAddr()const{return address;}
    const int getDirBlockNo()const{return blockNo;}

    int getFileBolckNo(string filename);

    void dirLogin(string name,string psw);
    void dirLogout(string name){subuser.logout(name);}
    bool isUnique(string filename);
    bool createFile(string filename,bitset<4> proc=bitset<4>(string("1100")),
                    string content="hello world!",string author="");
    bool deleteFile(string filename);

    // 提供块号是因为在读写文件之前需要打开文件，这个操作会获得块号
    string readfile(int block);
    bool writefile(int block,string content);
    bool isDeleted(int block);

    void print();
    void listFile();
};

#endif // USERDIR_H_INCLUDED
