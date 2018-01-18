/*
 * process_test.h
 *
 *  Created on: 2018��1��11��
 *      Author: chixinyang
 */

#ifndef PROCESS_TEST_H_
#define PROCESS_TEST_H_

#include <iostream>
#include "unp.h"
#include "apue.h"
#include <sys/wait.h>
using namespace std;
/* ������execlp
      ͷ�ļ���    #include<unistd.h>
      ���庯����int execlp(const char * file,const char * arg,....);
      ����˵����execlp()���PATH ����������ָ��Ŀ¼�в��ҷ��ϲ���file���ļ������ҵ����ִ�и��ļ���
                         Ȼ�󽫵ڶ����Ժ�Ĳ����������ļ���argv[0]��argv[1]���������һ�����������ÿ�ָ��(NULL)��������
                         ����ó���0����ʾһ����ָ�룬����뽫��ǿ��ת��Ϊһ���ַ�ָ�룬������������Ϊ���β�����
                         ���һ���������ĳ�����char * �ĳ��Ȳ�ͬ����ôexec������ʵ�ʲ����ͽ���������������óɹ�,
                         �����Լ���ִ�д���ͻ��ɼ��س���Ĵ���,execlp()��ߵĴ��ߵĴ���Ҳ�Ͳ���ִ����.
       ������exit
       ����:�����˳����򣬲����������ֵ����exit(127)
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
        while(fgets(buf,MAXLINE,stdin)!=NULL)   //�ӱ�׼�����ȡһ���ַ�����buf������'\n'�ж��Ƿ�����β
        {
            if(buf[MAXLINE-1]=='\n')            //��ΪҪ����exec������exec�����жϽ�β�ı�־��NULL������ת��\nΪNULL
                buf[MAXLINE-1]=0;
            cout<<"***now pid = "<<getpid()<<endl;
            if( (pid=fork()) < 0 ) //fork����ֻ�ڸ����̵���һ�Σ�֮����������ӽ����Ǹ����̵ĸ��ƣ�����Ҳ���з���ֵ���ӽ����з����㣬�������з����ӽ���pid
                err_sys("fork error");
            else if (pid==0)   //��ǰ������ child process
            {
                cout<<"***In child pid :"<<pid<<endl;
                execlp(buf,buf,NULL);
                err_ret("could not execute : %s",buf);
                exit(127);
            }
            else if( (pid=waitpid(pid,&status,0)) <0 )   //��ǰ�����Ǹ�����     �����ӽ���ִ����󷵻�
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
