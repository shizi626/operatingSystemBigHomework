#ifndef MYNODE_H_INCLUDED
#define MYNODE_H_INCLUDED

#include <iostream>
#include <string>
using namespace std;

class Mynode{
private:
    string nodename;
    int blockNo;
    bool deleted;

public:
    Mynode(string name,int number):
        nodename(name),blockNo(number),deleted(false){};
    Mynode():
        nodename(""),blockNo(-1),deleted(false){};

    const string getNodename()const{return nodename;}
    const int getBlockNo()const {return blockNo;}
    const bool isDeleted() const {return deleted;}// true if the node is deleted
    void setDeleted(bool del){deleted=del;}

    void setNodename(string name){nodename=name;}
    void setBlockNo(int num){blockNo=num;}
};


#endif // MYNODE_H_INCLUDED
