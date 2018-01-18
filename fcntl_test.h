/*
 * fcntl_test.h
 *
 *  Created on: 2018��1��15��
 *      Author: chixinyang
 */

#ifndef FCNTL_TEST_H_
#define FCNTL_TEST_H_
#include <iostream>
#include "unp.h"
#include "apue.h"
#include <limits.h>
#include <time.h>
#include <fcntl.h>
using namespace std;

/*void compare_ISOC_clock_And_POSIX_time()
{
    clock_t isoc_c;
    clock_t posix_t;
}*/
void test_lseek()  //���Ա�׼�����ܷ�����ƫ����
{
    off_t curpos;  //off_t  �ļ�ƫ����
    if( (curpos=lseek(STDIN_FILENO,0,SEEK_CUR)) == -1)
    {
        cout<<"the stdin_fileno could not support offset"<<endl;
    }
    else
        cout<<"seek ok! The curpos is :"<<curpos<<endl;
}
void file_control()
{
    int fd;
    char buf1[10]="123456789";
    char buf2[10]="abcdefghi";
    if( (fd=creat("file.hole",FILE_MODE)) < 0)   //�����ļ��������ļ�������������������ļ����ֺ��ļ�Ȩ��
    {
        err_sys("file create error !");
    }
    if( write(fd,buf1,10) != 10)                //����д�볤��
    {
        err_sys("file write error !");
    }
    if( lseek(fd,16000,SEEK_SET) == -1 )       //-1 �������������ļ�ƫ����,����ƫ����
     {
        err_sys("could not set offset");
    }
    if( write(fd,buf2,10) != 10)
    {
        err_sys("file write error !");
    }
}
void test_fcntl(int argc,char** argv){
    int val;
    if(argc != 2)
        err_quit("usage:./a.out <descriptor#>");
    if( (val=fcntl(atoi(argv[1]),F_GETFL,0 )) < 0)  //��ȡ�ļ�״̬��Ϣ��С��0��ʾʧ�ܡ�file control �����ļ�������������Ҫ��int����
        err_sys("fcntl error to fd %s !",argv[1]);
    switch(val & O_ACCMODE)
    {
        case O_RDONLY:
            cout<<"read only !";
            break;
        case O_WRONLY:
            cout<<"write only !";
            break;
        case O_RDWR:
            cout<<"read and write !";
            break;
        default:
            cout<<"unkown access mode !";
    }
    if(val & O_APPEND)    //׷�ӵ��ļ�β��
        cout<<", append";
    if(val & O_NONBLOCK)  //������ģʽ
        cout<<", nonblocking";
    if(val & O_SYNC)
        cout<<", syschronous write";  // �ȴ�д��ɣ����ݺ����ԣ�
#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SUNC)
    if(val & O_SYNC)
        cout<<", O_FSYNC :syschronous write";  // �ȴ�д��ɣ����ݺ�����
#endif
     cout<<endl;
}




#endif /* FCNTL_TEST_H_ */
