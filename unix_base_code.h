/*
 * unix_tcp_server.h
 *
 *  Created on: 2018��1��9��
 *      Author: chixinyang
 */

#ifndef UNIX_BASE_CODE_H_
#define UNIX_BASE_CODE_H_
#include "unp.h"
#include <time.h>
enum {MAXBUFF =2048};
void bzero (void *block, size_t size);
void SetSockaddr(struct sockaddr_in& sockaddr,int family,uint32_t addr,uint16_t port){
   bzero(&sockaddr,sizeof(sockaddr));  //��ʼ����ַ�ṹ
   sockaddr.sin_family=family;
   sockaddr.sin_addr.s_addr=htonl(addr);
   sockaddr.sin_port=htons(port);
}
void tec_server(){
       int listenfd,connfd;
       struct sockaddr_in servaddr,client_addr;
       char buff[MAXBUFF];

       //����IPv4 TCPЭ����׽ӿڣ����ص�����ֵ�Ǵ������׽ӿ��ļ���������
       listenfd=Socket(AF_INET,SOCK_STREAM,0);

       /* ������Ҫ�ĵ�ַ�ṹ
        * ����Ҫ�Ѷ���ȫ����ʼ������Ϊsocket_len�������������Ա����Ҫ��ʼ����
        * Ȼ�����Э���壬��ַ���˿ں�
        * htonl :��32λ�ĵ�ַ�������ֽ���ת�������ֽ���
        * htons :�������Ӵ������ֽ���ת�������ֽ���
        */
       SetSockaddr(servaddr,AF_INET,INADDR_ANY,13);
       //���׽ӿں͵�ַ��
       bind(listenfd,(SA*)&servaddr,sizeof(servaddr));//ת����ͨ�õ�ַ����SA
       //���׽���ת�ɼ����׽��֣������ں˼������׽ӿڣ����涨�����������
       Listen(listenfd,LISTENQ);

       //�ͻ��˵�ַ����
       int addr_size=sizeof(client_addr);  //�ñ�������ֵ�����������������ȥ���ֵ������ʵ��ֵ
       while(1)
       {
           connfd=Accept(listenfd,(SA*)&client_addr,&addr_size);  //�������ֽ������ӣ�����������
           time_t ticks;
           ticks=time(0);
           snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ticks));
           Write(connfd,buff,sizeof(buff));

           Close(connfd);  //�Ĵ����ֹر�����
       }
}

#endif /* UNIX_BASE_CODE_H_ */
