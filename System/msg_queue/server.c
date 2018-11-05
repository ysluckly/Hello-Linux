#include "common.h"

int main()
{
    int msgid = CreatMsgQueue();

    char buf[1024];

    while(1)
    {
         buf[0] = 0;
         RecvMsg(msgid,CLIENT_TYPE,buf);
         printf("client# %s\n",buf);

         printf("Please Enter# ");
         fflush(stdout);

         ssize_t s = read(0,buf,sizeof(buf));
         if(s>0)
         {
             buf[s-1] = 0;
             SendMsg(msgid,SERVER_TYPE,buf);
             printf("Send Done, Waiting recv...\n");
         }
    }
  DestroyMsg(msgid);
   return 0;
}
