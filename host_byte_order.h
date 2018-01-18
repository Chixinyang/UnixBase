/*
 * host_byte_order.h
 *
 *  Created on: 2018Äê1ÔÂ9ÈÕ
 *      Author: chixinyang
 */

#ifndef HOST_BYTE_ORDER_H_
#define HOST_BYTE_ORDER_H_
#include <iostream>
#include <iomanip>
#include "unp.h"
using namespace std;

void get_host_byte_order(){
    union{
        short s;
        char c[sizeof(short)];
    }un;
    un.s=0x0102;
    cout<<CPU_VENDOR_OS<<"  sizeof(short)="<<sizeof(short)<<" un.s="<<un.s<<"  hex=0x"
        <<hex<<setw(4)<<setfill('0')<<right<<un.s<<endl;
    if(un.c[0]==2){
        cout<<"the host byte order is little-endian"<<endl;
    }
    else if(un.c[1]==2){
        cout<<"the host byte order is big-endian"<<endl;
    }
}



#endif /* HOST_BYTE_ORDER_H_ */
