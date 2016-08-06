#include <iostream>
#include <string>
#include <bitset>
#include <iomanip>

#include "myfile.h"
#include "userdir.h"
#include "user.h"

using namespace std;

Userdir::Userdir()
    :address("/default"),nodeNow(0),blockNo(-1)
{
    subuser=User();
    for(int i=0;i<fileNumber;++i){
        nodeList[i]=Mynode();
    }
    for(int i=0;i<fileNumber;++i){
        fileList[i]=Myfile();
    }
}

Userdir::Userdir(string username,string userpsw,int block)
    :address("/"+username),nodeNow(0),blockNo(block)
{
    subuser=User(username,userpsw);
    for(int i=0;i<fileNumber;++i){
        nodeList[i]=Mynode();
    }
    for(int i=0;i<fileNumber;++i){
        fileList[i]=Myfile();
    }
}

int Userdir::getFileBolckNo(string filename){
    if(nodeNow==0){
        cout<<"no file at all!"<<endl;
        return -1;
    }
    for (int i = 0; i < nodeNow; ++i)
    {
        if(nodeList[i].getNodename()==filename){
            if (nodeList[i].isDeleted()==true)
            {
                cout<<"the file had been deleted!"<<endl;
                return -1;
            }
            return nodeList[i].getBlockNo();
        }
    }
    cout<<"cannot find this file!"<<endl;
    return -1;
}

void Userdir::dirLogin(string name,string psw){
    subuser.login(name,psw);
}

bool Userdir::isUnique(string filename){
    if(nodeNow==0){
        return true;
    }
    for(int i=0;i<nodeNow;++i){
        if(nodeList[i].getNodename()==filename&&nodeList[i].isDeleted()==false){
            return false;
        }
    }
    return true;
}

bool Userdir::createFile(string filename,bitset<4> proc,
                         string content,string author){
    if(subuser.getIsLogin()==false){
        // login before creation
        cout<<"you are not login! please login first!"<<endl;
        return false;
    }

    if(!isUnique(filename)){
        cout<<"filename already exists!"<<endl;
        return false;
    }
    string dir=getDirAddr();
    if(nodeNow==0){
        // if no file at all, so create it from scratch
        if(author==""){
            author=subuser.getUserName();
        }
        fileList[nodeNow]=Myfile(filename,dir,proc,content,author,nodeNow);
        nodeList[nodeNow]=Mynode(filename,nodeNow);
        nodeNow++;
        return true;
    }
    for(int i=0;i<nodeNow;++i){
        if(nodeList[i].isDeleted()==true){
        // if there is a deleted node in the nodeList, overwrite it
            int block=nodeList[i].getBlockNo();
            nodeList[i].setNodename(filename);
            nodeList[i].setBlockNo(block);
            fileList[block]=Myfile(filename,dir,proc,content,author,block);
            return true;
        }
    }

    // no deleted file, append it.
    if(nodeNow>=fileNumber){
        cout<<"no more room for creating!"<<endl;
        return false;
    }
    fileList[nodeNow]=Myfile(filename,dir,proc,content,author,nodeNow);
    nodeList[nodeNow]=Mynode(filename,nodeNow);
    nodeNow++;
    return true;
}

// delete file
// just label the file as deleted
bool Userdir::deleteFile(string filename){
    if(subuser.getIsLogin()==false){
        // login before deletion
        cout<<"you are not login! please login first!"<<endl;
        return false;
    }
    for(int i=0;i<nodeNow;++i){
        if(nodeList[i].getNodename()==filename){
            nodeList[i].setDeleted(true);
            return true;
        }
    }
    cout<<"cannot find this file!"<<endl;
    return false;
}

// return true if the file corresponding to the block is deleted
bool Userdir::isDeleted(int block){
    for(int i=0;i<nodeNow;++i){
        if(nodeList[i].getBlockNo()==block){
            if(nodeList[i].isDeleted()){
                cout<<"the file is deleted!"<<endl;
                return true;
            }
            else
                return false;
        }
    }
    cout<<"the file is not found!"<<endl;
    return true;
}

string Userdir::readfile(int block){

    if(isDeleted(block)){
        return "";
    }

    bitset<1> bit=fileList[block].getProtectedBit()[1];
    if(bit.test(0)==false&&subuser.getIsLogin()==false){
        cout<<"you have no right to read this file.\n please login first!"<<endl;
        return "";
    }
    string content=fileList[block].getContent();
    return content;
}

bool Userdir::writefile(int block,string content){

    if(isDeleted(block)){
        return "";
    }

    bitset<1> bit=fileList[block].getProtectedBit()[0];
    if(bit.test(0)==false&&subuser.getIsLogin()==false){
        cout<<"you have no right to write this file.\n please login first!"<<endl;
        return false;
    }
    fileList[block].writeFile(content);
    return true;
}

void Userdir::print(){
    cout<<left<<setw(20)<<getDirName()<<setw(20)<<getDirBlockNo()<<endl;
}

void Userdir::listFile(){
    cout<<left;
    cout<<setw(20)<<"filename"<<setw(20)<<"address"<<setw(20)<<"protected bit"<<setw(20)<<"file length"<<endl;
    for(int i=0;i<nodeNow;++i){
        if(!nodeList[i].isDeleted()){
            fileList[i].print();
        }
    }
}
