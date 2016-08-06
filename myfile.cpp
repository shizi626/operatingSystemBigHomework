#include <iostream>
#include "myfile.h"
#include <string>

using namespace std;

Myfile::Myfile(string name,string addr,bitset<4> bit,string content,string author,int block):
    filename(name),protectedBit(bit),fileContent(content),fileAuthor(author),blockNo(block)
{
    fileLength=content.length();
    fileAddress=addr+"/"+name;
}

string Myfile::readFile(){
    return this->getContent();
}

bool Myfile::writeFile(string content){
    this->fileContent=content;
    cout<<"write to file successfully!"<<endl;
    this->fileLength=content.length();
    return true;
}

void Myfile::print(){
    cout<<left<<setw(20)<<getFileName()<<setw(20)<<getFileAddress()
        <<setw(20)<<getProtectedBit()<<setw(20)<<getFileLength()<<endl;
}
