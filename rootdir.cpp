#include <iostream>

#include "rootdir.h"
#include "userdir.h"
#include "user.h"

using namespace std;

Rootdir::Rootdir():
    address("/"),nodeNow(0)
{
    for(int i=0;i<dirNumber;++i){
        nodeList[i]=Mynode();
        dirList[i]=Userdir();
    }
    rootuser=User("/","123");
}

void Rootdir::rootLogin(string name,string psw){
    rootuser.login(name,psw);
}

bool Rootdir::isUnique(string dirname){
    for(int i=0;i<nodeNow;++i){
        if(nodeList[i].getNodename()==dirname&&nodeList[i].isDeleted()==false){
            return false;
        }
    }
    return true;
}

int Rootdir::getDirBlock(string dirname){
    if(nodeNow==0){
        cout<<"no directory at all!"<<endl;
        return -1;
    }

    for (int i = 0; i < nodeNow; ++i)
    {
        if(nodeList[i].getNodename()==dirname){
            if (nodeList[i].isDeleted()==true)
            {
                cout<<"the directory had been deleted!"<<endl;
                return -1;
            }
            return nodeList[i].getBlockNo();
        }
    }
    cout<<"cannot find this directory!"<<endl;
    return -1;
}

bool Rootdir::createDir(string username,string userpsw){
    if(rootuser.getIsLogin()==false){
        // login before creation
        cout<<"you are not login! please login first!"<<endl;
        return false;
    }

    if(!isUnique(username)){
        cout<<"directory name already exists!"<<endl;
        return false;
    }

    string dir=getRootAddr();
    if(nodeNow==0){
        // if no directory at all, so create it from scratch
        dirList[nodeNow]=Userdir(username,userpsw,nodeNow);
        nodeList[nodeNow]=Mynode(username,nodeNow);
        nodeNow++;
        return true;
    }
    for(int i=0;i<nodeNow;++i){
        if(nodeList[i].isDeleted()==true){
        // if there is a deleted node in the nodeList, overwrite it
            int block=nodeList[i].getBlockNo();
            nodeList[i].setNodename(username);
            nodeList[i].setBlockNo(block);
            dirList[block]=Userdir(username,userpsw,nodeNow);
            return true;
        }
    }

    if(nodeNow>=dirNumber){
        cout<<"no more room for creating!"<<endl;
        return false;
    }
    // no deleted directory, append it.
    dirList[nodeNow]=Userdir(username,userpsw,nodeNow);
    nodeList[nodeNow]=Mynode(username,nodeNow);
    nodeNow++;
    return true;
}

bool Rootdir::deleteDir(string username){
    if(rootuser.getIsLogin()==false){
        // login before deletion
        cout<<"you are not login! please login first!"<<endl;
        return false;
    }
    for(int i=0;i<nodeNow;++i){
        if(nodeList[i].getNodename()==username){
            nodeList[i].setDeleted(true);
            return true;
        }
    }
    cout<<"cannot find this directory!"<<endl;
    return false;
}

void Rootdir::listDir(){
    cout<<left;
    cout<<setw(20)<<"dirname"<<setw(20)<<"address"<<endl;
    for(int i=0;i<nodeNow;++i){
        if(!nodeList[i].isDeleted()){
            dirList[i].print();
        }
    }
}


bool Rootdir::dirLogin(string dirname,string dirpsw){
    int dirBlock=getDirBlock(dirname);
    string diruser=dirList[dirBlock].getDirName();
    dirList[dirBlock].dirLogin(diruser,dirpsw);
    return true;
}

void Rootdir::dirLogout(string dirname){
    int dirBlock=getDirBlock(dirname);
    dirList[dirBlock].dirLogout(dirname);
}

int Rootdir::openFile(string dirname,string filename){
    int dirBlock=getDirBlock(dirname);
    return dirList[dirBlock].getFileBolckNo(filename);
}

string Rootdir::readFile(string dirname,int fileBlock){
    int dirBlock=getDirBlock(dirname);
    return dirList[dirBlock].readfile(fileBlock);
}

void Rootdir::writeFile(string dirname,int fileBlock,string content){
    int dirBlock=getDirBlock(dirname);
    dirList[dirBlock].writefile(fileBlock,content);
}

bool Rootdir::createFile(string dirname,string filename,bitset<4> proc,string content,string author){
    int dirBlock=getDirBlock(dirname);
    return dirList[dirBlock].createFile(filename,proc,content,author);
}

bool Rootdir::deleteFile(string dirname,string filename){
    int dirBlock=getDirBlock(dirname);
    return dirList[dirBlock].deleteFile(filename);
}

void Rootdir::listDirFile(string dirname){
    int dirBlock=getDirBlock(dirname);
    dirList[dirBlock].listFile();
}
