/*
 * unix_tcp_server.h
 *
 *  Created on: 2018年1月9日
 *      Author: chixinyang
 */

#ifndef UNIX_BASE_CODE_H_
#define UNIX_BASE_CODE_H_
#include "unp.h"
#include <time.h>
enum {MAXBUFF =2048};
void bzero (void *block, size_t size);
void SetSockaddr(struct sockaddr_in& sockaddr,int family,uint32_t addr,uint16_t port){
   bzero(&sockaddr,sizeof(sockaddr));  //初始化地址结构
   sockaddr.sin_family=family;
   sockaddr.sin_addr.s_addr=htonl(addr);
   sockaddr.sin_port=htons(port);
}
void tec_server(){
       int listenfd,connfd;
       struct sockaddr_in servaddr,client_addr;
       char buff[MAXBUFF];

       //定义IPv4 TCP协议的套接口，返回的整数值是创建的套接口文件的描述符
       listenfd=Socket(AF_INET,SOCK_STREAM,0);

       /* 定义需要的地址结构
        * 首先要把对象全部初始化，因为socket_len类型中有数组成员，需要初始化。
        * 然后添加协议族，地址，端口号
        * htonl :把32位的地址从主机字节序转成网络字节序
        * htons :把整数从从主机字节序转成网络字节序
        */
       SetSockaddr(servaddr,AF_INET,INADDR_ANY,13);
       //把套接口和地址绑定
       bind(listenfd,(SA*)&servaddr,sizeof(servaddr));//转换成通用地址类型SA
       //把套接字转成监听套接字，允许内核监听该套接口，并规定最大链接数量
       Listen(listenfd,LISTENQ);

       //客户端地址长度
       int addr_size=sizeof(client_addr);  //该变量属于值——结果参数，传进去最大值，返回实际值
       while(1)
       {
           connfd=Accept(listenfd,(SA*)&client_addr,&addr_size);  //三次握手建立链接，并接受数据
           time_t ticks;
           ticks=time(0);
           snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ticks));
           Write(connfd,buff,sizeof(buff));

           Close(connfd);  //四次握手关闭连接
       }
}

#endif /* UNIX_BASE_CODE_H_ */
