#include <iostream>
#include <bitset>

#include "user.h"
#include "myfile.h"
#include "mynode.h"
#include "userdir.h"
#include "rootdir.h"


using namespace std;

void testnode(){
    Mynode node=Mynode("node",2);
    cout<<node.getNodename()<<":"<<node.getBlockNo()<<endl;
}

void testuser(){
    User user=User("zhang","123");
    //user.login("zhang","123");
    cout<<user.getUserName()<<endl;
    user.logout("zhang");
}

void testfile(){
    Myfile file=Myfile("txt","d:/",bitset<4>(string("1111")),"hello world!","david",9);
    cout<<file.getContent()<<endl;
    cout<<file.getFileAddress()<<endl;
    cout<<file.getFileAuthor()<<endl;
    cout<<file.getFileLength()<<endl;
    cout<<file.getFileName()<<endl;
    cout<<file.getProtectedBit()<<endl;
    cout<<file.getBlockNo()<<endl;
    cout<<file.readFile()<<endl;
    file.print();
    file.writeFile("ok!");
    cout<<file.readFile()<<endl;
}

void testsub(){
    Userdir sub=Userdir("zhang","123",1);
    cout<<sub.getDirAddr()<<endl;
    cout<<sub.getDirName()<<endl;
    cout<<sub.getDirBlockNo()<<endl;

    sub.createFile("hello",bitset<4>(string("1100")));
    sub.dirLogin("zhang","123");
    sub.createFile("hello",bitset<4>(string("1100")));
    sub.createFile("hello1",bitset<4>(string("1100")));  //test for uniqueness
    sub.readfile(0);
    sub.readfile(1);
    sub.listFile();
    int block=sub.getFileBolckNo("hello");
    cout<<sub.readfile(block)<<endl;
    sub.writefile(block,"haha");
    cout<<sub.readfile(block)<<endl;
    sub.deleteFile("hello");
    cout<<sub.readfile(block)<<endl;
}

void testroot(){
    Rootdir root=Rootdir();
    cout<<root.getRootAddr()<<endl;
    root.createDir("c");
    root.rootLogin("/","123");
    root.createDir("c");
    root.createDir("c");

    root.dirLogin("c");
    root.createFile("c","aaa");
    root.createFile("c","aaa");
    int file=root.openFile("c","aaa");
    cout<<root.readFile("c",file)<<endl;
    root.writeFile("c",file,"jjj");
    root.listDirFile("c");
    root.deleteFile("c","aaa");
    root.listDirFile("c");

    root.createDir("d"); //test for uniqueness
    root.listDir();
    cout<<root.getDirBlock("c")<<endl;
    root.deleteDir("c");
    cout<<root.getDirBlock("c")<<endl;
}




Rootdir root=Rootdir();
string currentFileName="";
int currentFileBlock=-1;
string currentDirName="";
int currentDirBlock=-1;

void login(string password){
    if(currentDirName==""){
        root.rootLogin("/",password);
        return;
    } else {
        root.dirLogin(currentDirName,password);
        return;
    }
}

void logout(){
    if(currentDirName==""){
        root.rootLogout();
        return;
    } else {
        root.dirLogout(currentDirName);
        return;
    }
}

void showList(){
    if(currentDirName==""){
        root.listDir();
        return;
    } else {
        root.listDirFile(currentDirName);
        return;
    }
}

void createDir(string dirname){
    if(currentDirName!=""){
        cout<<"�����������ļ��У����ȷ������ļ��У�"<<endl;
        return;
    }
    root.createDir(dirname);
    cout<<"�ɹ������ļ��У�"<<dirname<<endl;
}

void deleteDir(string dirname){
    if(currentDirName!=""){
        cout<<"�����������ļ��У����ȷ������ļ��У�"<<endl;
        return;
    }
    root.deleteDir(dirname);
}

void enterDir(string dirname){
    // in sub directory
    if(currentDirName!=""){
        if(dirname==".."){
            currentDirName="";
            currentDirBlock=-1;
            return;
        }else{
            cout<<"�����������ļ��У����ȷ������ļ��У�"<<endl;
            return;
        }
    }
    // in root directory
    int block=root.getDirBlock(dirname);
    if(block==-1){
        return;
    }
    currentDirName=dirname;
    currentDirBlock=block;
}

void createFile(string filename){
    if(currentDirName==""){
        cout<<"���Ƚ���һ�����ļ��У�"<<endl;
        return;
    }
    root.createFile(currentDirName,filename);
    cout<<"�ɹ������ļ���"<<filename<<endl;
}

void delFile(string filename){
    if(currentDirName==""){
        cout<<"���Ƚ���һ�����ļ��У�"<<endl;
        return;
    }
    root.deleteFile(currentDirName,filename);
}

void openFile(string dirname,string filename){
    int file=root.openFile(dirname,filename);
    if(file==-1){
        cout<<"���ļ�ʧ�ܣ�"<<endl;
        return;
    }
    currentFileBlock=file;
    currentFileName=filename;
    cout<<"���ļ�"<<filename<<"�ɹ�"<<endl;
}

void closeFile(){
    currentFileBlock=-1;
    currentFileName="";
}

void readFile(string filename){
    if(currentDirName==""){
        cout<<"���Ƚ���һ�����ļ��У�"<<endl;
        return;
    }
    if(filename!=currentFileName){
        cout<<"���ȴ��ļ���"<<endl;
    }
    cout<<"�ļ����ݣ�"<<root.readFile(currentDirName,currentFileBlock)<<endl;
}

void writeFile(string filename,string content){
    if(currentDirName==""){
        cout<<"���Ƚ���һ�����ļ��У�"<<endl;
        return;
    }
    if(filename!=currentFileName){
        cout<<"���ȴ��ļ���"<<endl;
    }

    root.writeFile(currentDirName,currentFileBlock,content);
}

void mainloop(){

    string command;
    string para1;
    string para2;

    cout<<"��ӭ����myinux�ļ�ϵͳ������Ϊָ���ʽ��"<<endl
        <<"login password"<<"��¼��ǰ�ļ��е��˻�"<<endl
        <<"logout"<<"�˳���ǰ�ļ��е��˻�"<<endl
        <<"dir"<<"�е�ǰ�ļ��е�Ŀ¼"<<endl
        <<"createDir directoryName"<<"����Ŀ¼�´���һ���µ��û��ļ��У���Ҫ��¼��"<<endl
        <<"deleteDir directoryName"<<"����Ŀ¼��ɾ��һ���û��ļ��У���Ҫ��¼��"<<endl
        <<"cd directoryName"<<"����ĳ�����ļ���"<<endl
        <<"create filename"<<"�ڵ�ǰ�û��ļ����ڴ����ļ�����Ҫ��¼��"<<endl
        <<"delete filename"<<"�ڵ�ǰ�û��ļ�����ɾ���ļ�����Ҫ��¼��"<<endl
        <<"open dirname filename"<<"��ָ���ļ�����ָ���ļ�"<<endl
        <<"close"<<"�ر��Ѵ򿪵��ļ�"<<endl
        <<"read filename"<<"��ȡ�Ѿ��򿪵��ļ������ݣ������ļ������������Ҫ��¼��"<<endl
        <<"write filename content"<<"���Ѿ��򿪵��ļ���д���ݣ������ͣ������ļ������������Ҫ��¼��"<<endl
        <<"exit"<<"�˳���ϵͳ"<<endl;

    while(true){
        cout<<"/"<<currentDirName<<"/:";

        cin>>command;

        if (command=="login"){
            cin>>para1;
            login(para1);
            continue;
        }
        if (command=="logout"){
            logout();
            continue;
        }
        if (command=="dir"){
            showList();
            continue;
        }
        if (command=="createDir"){
            cin>>para1;
            createDir(para1);
            continue;
        }
        if (command=="deleteDir"){
            cin>>para1;
            deleteDir(para1);
            continue;
        }
        if (command=="cd"){
            cin>>para1;
            enterDir(para1);
            continue;
        }
        if (command=="create"){
            cin>>para1;
            createFile(para1);
            continue;
        }
        if (command=="delete"){
            cin>>para1;
            delFile(para1);
            continue;
        }
        if (command=="open"){
            cin>>para1;
            cin>>para2;
            openFile(para1,para2);
            continue;
        }
        if (command=="close"){
            closeFile();
            continue;
        }
        if (command=="read"){
            cin>>para1;
            readFile(para1);
            continue;
        }
        if (command=="write"){
            cin>>para1;
            cin>>para2;
            writeFile(para1,para2);
            continue;
        }
        if (command=="exit"){
            cout<<"�˳�ϵͳ��"<<endl;
            break;
        }
        cout<<"δ����ָ����������룡"<<endl;
    }
}



int main()
{
    /*rootȱ��read file��write file����*/
    //testuser();
    //testfile();
    //testnode();
    //testsub();
    //testroot();
    mainloop();
    return 0;
}
