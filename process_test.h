/*
 * process_test.h
 *
 *  Created on: 2018年1月11日
 *      Author: chixinyang
 */

#ifndef PROCESS_TEST_H_
#define PROCESS_TEST_H_

#include <iostream>
#include "unp.h"
#include "apue.h"
#include <sys/wait.h>
using namespace std;
/* 函数：execlp
      头文件：    #include<unistd.h>
      定义函数：int execlp(const char * file,const char * arg,....);
      函数说明：execlp()会从PATH 环境变量所指的目录中查找符合参数file的文件名，找到后便执行该文件，
                         然后将第二个以后的参数当做该文件的argv[0]、argv[1]……，最后一个参数必须用空指针(NULL)作结束。
                         如果用常数0来表示一个空指针，则必须将它强制转换为一个字符指针，否则它将解释为整形参数，
                         如果一个整形数的长度与char * 的长度不同，那么exec函数的实际参数就将出错。如果函数调用成功,
                         进程自己的执行代码就会变成加载程序的代码,execlp()后边的代边的代码也就不会执行了.
       函数：exit
       功能:立即退出程序，并返回其参数值，如exit(127)
 */
void sig_int(int sigl){
    cout<<"interrupt"<<endl;
}
void process_test(){
    //    cout<<"***the process id is "<<getpid()<<endl;   // pid_t  is int
        char buf[MAXLINE];
        pid_t pid;
        int status;
        cout<<"%";
        signal(SIGINT,sig_int);
        while(fgets(buf,MAXLINE,stdin)!=NULL)   //从标准输入读取一行字符串到buf，根据'\n'判断是否是行尾
        {
            if(buf[MAXLINE-1]=='\n')            //因为要传给exec函数，exec函数判断结尾的标志是NULL，所以转换\n为NULL
                buf[MAXLINE-1]=0;
            cout<<"***now pid = "<<getpid()<<endl;
            if( (pid=fork()) < 0 ) //fork函数只在父进程调用一次，之后出现由于子进程是父进程的复制，所以也会有返回值，子进程中返回零，父进程中返回子进程pid
                err_sys("fork error");
            else if (pid==0)   //当前进程是 child process
            {
                cout<<"***In child pid :"<<pid<<endl;
                execlp(buf,buf,NULL);
                err_ret("could not execute : %s",buf);
                exit(127);
            }
            else if( (pid=waitpid(pid,&status,0)) <0 )   //当前进程是父进程     等在子进程执行完后返回
            {
                err_sys("wait pid error!");
            }
            else
            {
               cout<<"***In parent pid -> my child pid is :"<<pid <<endl;
            }
            cout<<"%";
        }
        exit(0);
}



#endif /* PROCESS_TEST_H_ */
