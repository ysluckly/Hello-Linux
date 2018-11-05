#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define PATHNAME "."
#define PROJ_ID 0x8298

#define CLIENT_TYPE 1
#define SERVER_TYPE 2

struct msgbuf
{
    long mytype;
    char mytext[64];
};

int CreatMsgQueue();//创建消息队列
int GetMsgQueue();//获取消息队列
void DestroyMsgQueue(int msgid);//销毁消息队列
int SendMsg(int msgid,int CLIENT,char* msg);//发送信息
int RecvMsg(int magid,int SERVER,char* msg);//接收信息


#endif //__COMMON_H__
