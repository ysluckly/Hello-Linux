#include "common.h"


static int CommMsgQueue(int flag)//创建消息队列
{
    key_t key = ftok(PATHNAME,PROJ_ID);
    if(key<0)
    {
        perror("ftok");
        return -1;
    }
    int msgid = msgget(key,flag);
    if(msgid<0)
    {
        perror("msgget");
        return -1;
    }

    return msgid;
}

int CreatMsgQueue()
{
    return CommMsgQueue(IPC_CREAT|IPC_EXCL|0666);
}
int GetMsgQueue()//获取消息队列
{
    return CommMsgQueue(IPC_CREAT);
}
void DestroyMsgQueue(int msgid)//销毁消息队列
{
    if(msgctl(msgid,IPC_RMID,NULL)<0)
    {
        perror("msgctl");
        printf("ERROR ");
  }
    
    printf("销毁成功");
}
int SendMsg(int msgid,int CLIENT,char* msg)//发送信息
{
    struct msgbuf huf;
    huf.mytype = CLIENT;
    strcpy(huf.mytext,msg);

    if(msgsnd(msgid,(void*)&huf,64,0)<0)
    {
        perror("msgsnd");
        return -1;
    }

    return 0;

}
int RecvMsg(int msgid,int SERVER,char* msg)//接收信息
{
    struct msgbuf buf;
    if(msgrcv(msgid,(void*)&buf,64,SERVER,0)<0)
    {
        perror("msgrcv");
        return -1;
    }

    strcpy(msg,buf.mytext);
    return 0;
}
