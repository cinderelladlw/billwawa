#include "server.h"

int main(void)  
{  
    int sockfd;  
    int clientfd;  
    int sin_size;  
    int i;  
  
    struct sockaddr_in mote_addr;  
      
    sockfd = SetSocket(SERV_PORT);  
    if(sockfd == -1)  
        ServerSysError("Socket Create failed or Bind Error!/n");  
    LanuchServer(&sockfd);  
    if(sockfd == -1)  
        ServerSysError("Listen Error!/n");  
    signal(SIGPIPE, NotNetLink);  
  
    /*循环等待客户连接*/  
    while(1)  
    {  
        fprintf(stdout, "%s\n", "wait client....");  
        fflush(stdout);  
        /*阻塞等待连接到达*/  
        sin_size = sizeof(struct sockaddr_in);  
        if((clientfd = accept(sockfd, (struct sockaddr*)&mote_addr, &sin_size)) == -1)  
        {  
            ServerUserError("a user Accept error.");  
            continue;  
        }  
        fprintf(stdout, "Received a connection from %s\n", inet_ntoa(mote_addr.sin_addr));  
        fflush(stdout);  
        if(SendMsg("connect ok", clientfd) == -1)  
        {  
            ServerUserError("Send Msg to client Error!\n");  
            close(clientfd);  
            continue;  
        }  
        close(clientfd);//关闭连接  
    }  
    close(sockfd);//关闭端口的监听  
  
    return 0;     
}  
