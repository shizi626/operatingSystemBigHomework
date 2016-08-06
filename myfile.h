#ifndef MYFILE_H_INCLUDED
#define MYFILE_H_INCLUDED

#include <string>
#include <bitset>
#include <iomanip>

using namespace std;
class Myfile{
private:
     // �Ӹߵ��ͷֱ��ʾ�������ߣ�д�����ߣ������ÿͣ�д���ÿͣ�
     // 0 Ϊû��Ȩ�ޣ�1 Ϊ��Ȩ��
    bitset<4> protectedBit;
    int fileLength;

    string filename;
    string fileAddress;
    string fileContent;
    string fileAuthor;

    int blockNo;

public:
    Myfile():
        filename(""),fileAddress(""),protectedBit(bitset<4>(string("1111"))),fileContent(""),fileAuthor(""),blockNo(-1){};
    Myfile(string fname,string addr,bitset<4> bit,string content,string author,int block);

    const bitset<4> getProtectedBit()const{return protectedBit;}
    const int getFileLength()const{return fileLength;}

    const int getBlockNo()const{return blockNo;}
    const string getFileName()const{return filename;}
    const string getFileAddress()const{return fileAddress;}
    const string getContent()const{return fileContent;}
    const string getFileAuthor()const{return fileAuthor;}

    string readFile();
    bool writeFile(string content);

    void print();
};


#endif // MYFILE_H_INCLUDED
