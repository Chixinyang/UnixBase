/*
 * fcntl_test.h
 *
 *  Created on: 2018年1月15日
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
void test_lseek()  //测试标准输入能否设置偏移量
{
    off_t curpos;  //off_t  文件偏移量
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
    if( (fd=creat("file.hole",FILE_MODE)) < 0)   //创建文件，返回文件描述符，输入参数是文件名字和文件权限
    {
        err_sys("file create error !");
    }
    if( write(fd,buf1,10) != 10)                //返回写入长度
    {
        err_sys("file write error !");
    }
    if( lseek(fd,16000,SEEK_SET) == -1 )       //-1 代表不允许设置文件偏移量,返回偏移量
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
    if( (val=fcntl(atoi(argv[1]),F_GETFL,0 )) < 0)  //获取文件状态信息。小于0表示失败。file control 参数文件描述符，命令要求，int参数
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
    if(val & O_APPEND)    //追加到文件尾部
        cout<<", append";
    if(val & O_NONBLOCK)  //非阻塞模式
        cout<<", nonblocking";
    if(val & O_SYNC)
        cout<<", syschronous write";  // 等待写完成（数据和属性）
#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SUNC)
    if(val & O_SYNC)
        cout<<", O_FSYNC :syschronous write";  // 等待写完成（数据和属性
#endif
     cout<<endl;
}




#endif /* FCNTL_TEST_H_ */
