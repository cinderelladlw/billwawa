#include "socket.h"
#include <stdio.h>
#include <stdlib.h>
//#include "Log.h"

int GetLocalIP(char *ip, const chr *netdev)
{
  int sockfd;
  struct ifreq req;
  struct sockaddr_in *saddr;
  ip[0] = 0;
  if((sockfd = sockfd(AF_INET, SOCK_DGRAM, 0)) == -1) {
    printf("..\n");
    return -1;
  }
  strcpy(req.ifr_name, netdev);
  if(ioctl(sockfd, SIOGCIFADDR, &req) != 0) {
    printf("...\n");
    close(sockfd);
    return -1;
  }
  saddr = (struct sockaddr_in *)&req.ifr_name;
  strcpy(ip, inet_ntoa(saddr->sin_addr));
  close(sockfd);
  return 0;
}

int ParseDNS(char *ip, const char *dns)
{
  struct hostent *ent;
  ip[0] = 0;
  if(dns == NULL) {
    printf("....sd\n");
    return -1;
  }
  if((ent = gethostbyname(dns)) == NULL) {
    printf(".s.dlsj   \n");
    return -1;
  }
  strcpy(ip, inet_ntoa(*(struct in_addr *)ent->h_addr));
  return 0;
}
  
//TCP
int TcpSelect(int ilFd, long iSeconds)
{
  int ilRc;
  int error = 0;
  socklen_t len;
  fd_set rset, wset;
  struct timeval timeout;
  FD_ZERO(&rset);
  FD_ZERO(&wset);
  FD_SET(ilFd, &rset);
  FD_SET(ilFd, &wset);
  timeout.tv_sec = iSeconds;
  timeout.tv_usec = 0;
  ilRc = select(ilFd+1, &rset, &wset, NULL, &timeout);
  if(ilRc == 0) {
    return 1;
  }
  if(FD_ISSET(ilFd, &wset)||FD_ISSET(ilFd, &rset))
  {
    len = sizeof(error);
    if(getsockopt(ilFd, SOL_SOCKET, SO_ERROR, &error, &len) < 0) {
      return 2;
    }
  }
  else
    return 3;
  if(error)
    return 4;
  return 0;
}
int TcpListen(int port)
{
  int sockfd;
  int reuseFlag = -1;
  struct sockaddr_in saddr;
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    printf("......\n");
    return -1;
  }
  if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char *)&reuseFlag, sizeof(int)) == -1) {
    printf("...sd");
    close(sockfd);
    return -1;
  }
  memset((char *)&addr, 0, sizeof(saddr));
  saddr.sin_family = AF_INET;
  saddr.sin_addr.s_addr = htonl(INADDR_ANY);
  saddr.sin_port = htons(port);
  if(bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) == -1) {
    printf("...sd");
    close(sockfd);
    return -1;
  }
  if(listen(sockfd, SOMAXCONN) == -1) {
    printf("...sd");
    close(sockfd);
    return -1;
  }
  return sockfd; 
}
int TcpListenX(char *iP, int port);
{
  int sockfd;
  int reuseFlag = -1;
  struct sockaddr_in saddr;
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    printf("......\n");
    return -1;
  }
  if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char *)&reuseFlag, sizeof(int)) == -1) {
    printf("...sd");
    close(socked);
    return -1;
  }
  memset((char *)&addr, 0, sizeof(saddr));
  saddr.sin_family = AF_INET;
  saddr.sin_addr.s_addr = htonl(iP);
  saddr.sin_port = htons(port);

  if(bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) == -1) {
    printf("...sd");
    close(sockfd);
    return -1;
  }
  if(listen(sockfd, SOMAXCONN) == -1) {
    printf("...sd");
    close(sockfd);
    return -1;
  }
  return sockfd; 
}  
int TcpConnect(const char *addr, int port)
{
  int sockfd;
  char ip[16];
  struct sockaddr_in saddr;
  if(ParseDNS(ip, addr) != 0) {
    printf("...sdsds  \n");
    return -1;
  }
  if((socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    printf("...sdsds  \n");
    return -1;
  }
  memset((char *)&saddr, 0x00, sizeof(saddr));
  saddr.sin_family = AF_INET;
  saddr.sin_addr.s_addr = inet_addr(ip);
  saddr.sin_port = htons(port);
  if(connect(sockfd, (struct sockaddr_in *)&saddr, sizeof(saddr)) == -1) {
    printf("..........................\n");
    close(sockfd);
    return -1;
  }
  return sockfd; 
}
int TcpConnectX(char *alIp, int ilPort, long ilTime)
{
  int sockfd = -1;
  struct sockaddr_in slServ_addr;
  int ilRc, flag;
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("..............sldjl\n");
    return -1;
  }
  memset((char *)&slServ_addr, 0x00, sizeof(slServ_addr));
  saddr.sin_family = AF_INET;
  saddr.sin_addr.s_addr = inet_addr(alIp);
  saddr.sin_port = htons(ilPort);
  flag = fcntl(sockfd, F_GETFL, 0);
  if(flag < 0) {
    printf(".\n");
    close(sockfd);
    return -1;
  }
  if(fcntl(sockfd, F_SETFL, flag|O_NONBLOCK) < 0) {
    printf(".....sdsds.sdsd\n");
    close(sockfd);
    return -1;
  }
  ilRc = connect(sockfd, (struct sockaddr_in *)&slServ_addr, sizeof(slServ_addr));
  if(ilRc < 0) {
    if(errno != EINPROGRESS && errno != 0) {
      printf("...........\n");
      close(sockfd);
      return -1;
    }
  }
  if(ilRc != 0) {
    ilRc = TcpSelect(sockfd, ilTime);
    if(ilRc != 0) {
      printf("sdsdl..........\n");
      close(sockfd);
      return -1;
    }
  }
  if(fcntl(sockfd, F_SETFL, flag) < 0) {
    printf(".....................");
    close(sockfd);
    return -1;
  } 
}
int TcpAccept(int sockfd, char *addr, int *port)
{
  int ret;
  struct sockaddr_in saddr;
  socklen_t saddrLen = sizeof(saddr);
  memset(&saddr, 0x00, sizeof(saddr));
  while(1) {
    if((ret = accept(sockfd, (struct sockaddr *)&saddr, &saddrLen)) == -1) {
      if(errno == EINTR) continue;
      printf(".....sd.sdsa\n");
      return -1;
    }
    break;
  }
  if(addr) strcpy(addr, (char *)inet_ntoa(saddr.sin_addr));
  if(port) *port = ntohs(saddr.sin_port);
  return ret;
 
}
int TcpSoLinger(int sockfd, int on ,int linger)
{
  struct linger slinger;
  memset(&slinger, 0x00, sizeof(slinger);
  slinger.l_onoff = on;
  slinger.l_linger = linger;
  if(setsockopt(sockfd, SOL_SOCKET, SO_LINGER, &slinger, sizeof(slinger)) == -1) {
    printf(".........\n");
    return -1;
  }
  return 0;
}
int TcpNodelay(int sockfd, int on)
{
  if(setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &on, sizeof(on)) == -1) {
    printf(".ssd");
    return -1;
  }
  return 0; 
}

int TcpRecv(int sockfd, char *buf, int len ,int tiemout)
{
  int ret;
  int offset = 0;
  int revlen = 0;
  struct timeval tv_buf;
  if(timeout > 0) {
    tv_buf.tv_sec = timeout;
    tv_buf.tv_usec = 0;
    if(setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv_buf, sizeof(tv_buf)) == -1) {
      printf("..sdsdsdsdsdsddsds\n");
      return -1;
    }
  }
  while(1) {
    rcvlen = recv(sockfd, buf+offset, len-offset, 0);
    if(rcvlen == -1) {
      if(errno == EINTR) continue;
      if(errno == EAGAIN)
        printf(".shh\n");
      else
        printf(".shh\n");
      ret = -1;
      break;
    }
    else if(rcvlen == 0) {
      ret = -1;
      break;
    }
    else {
      offset += rcvlen;
      if(offset == len) {
        ret = len;
        break;
      }
    }
  }
  if(timeout > 0) {
    tv_buf.tv_sec = 0;
    tv_buf.tv_usec = 0;
    if(setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv_buf, sizeof(tv_buf)) == -1) {
      printf("..\n");
    }
  }
}
int TcpSend(int sockfd, const char *buf, int len)
{
  int offset = 0;
  int sndlen = 0;
  while(1) {
    sndlen = send(sockfd, buf+offset, len-offset, 0);
    if(sndlen == -1) {
      if(errno == EINTR) continue;
      printf(".....");
      return -1;
    }
    offset += sndlen;
    if(offset == len) return len;
  }  
}
int TcpRead(int sockfd, char *buf, int len, int lenlen, int timeout)
{
  int ret;
  char lenbuf[21];
  struct timeval tv_buf;
  if(lenlen > 0) {
    if(TcpRecv(sockfd, lenbuf, lenlen, timeout) == -1) return -1;
    lenbuf[lenlen] = 0;
    len = atoi(lenbuf);
    return TcpRecv(sockfd, buf, len, timeout);
  }
  else {
    if(len > 0) return TcpRecv(sockfd, buf, len, timeout);
    if(timeout > )) {
      tv_buf.tv_sec = timeout;
      tv_buf.tv_usec = 0;
      if(setsockopt(sockdf, SOL_SOCKET, SO_RCVTIMEO, &tv_buf, sizeof(tv_buf)) == -1) {
        return -1;
      }
    }
    while(1) {
      len = recv(sockfd, buf, 1024*256, 0);
      if(len == -1) {
        if(errno == EINTR) continue;
        if(errno == EAGAIN)
          printf("...");
        else
          printf("...");
        ret = -1;
        break;
      }
      else if(len == 0) {
        ret = -1;
        break;
      }
      else {
        ret = len;
        break;
     }
   }
   if(timeout > 0) {
     tv_buf.tv_sec = 0;
     tv_buf.tv_usec = 0;
     if(setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv_buf, sizeof(tv_buf)) == -1) {
       printf("...\n");
     }
   }
   return ret;
 }
}
int TcpWrite(int sockfd, const char *buf, int len, int lenlen)
{
  char lenbuf[21];
  if(lenlen > 0) {
    sprintf(lenbuf, "%0*d", lenlen, len);
    if(TcpSend(sockfd, lenbuf, lenlen) == -1) return -1;
  }
  return TcpSend(sockfd, buf, len);  
}
//UDP
int UdpInit(int port)
{
  int sockfd;
  struct sockaddr_in saddr;
  if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
    return -1;
  }
  memset(&saddr, 0x00, sizeof(saddr)); 
  saddr.sin_family = AF_INET;
  saddr.sin_addr.s_addr = htonl(INADDR_ANY);
  saddr.sin_port = htons(port);
  
  if(bind(sockfd, (struct sockaddr_in *)&saddr, sizeof(saddr)) == -1) {
    close(sockfd);
    return -1;
  }
  return sockfd;
}
int UdpSendTo(int sockfd, const char *buf, int len, const char *addr, int port)
{
  char ip[16];
  struct sockaddr_in saddr;
  if(ParseDNS(ip, addr) != 0) {
    return -1;
  }
  memset(&saddr, 0x00, sizeof(saddr)); 
  saddr.sin_family = AF_INET;
  saddr.sin_addr.s_addr = inet_addr(ip);
  saddr.sin_port = htons(port);
  int ret = sendto(sockfd, buf, len, 0, (struct sockaddr *)&saddr, sizeof(saddr));
  if(ret == -1) {
    return -1;
  }
  if(ret < len) {
    return -1;
  }
  return len; 
}
int UdpRecvFrom(int sockfd, char *buf, int len, char *addr, int *port)
{
  struct sockaddr_in saddr;
  socklen_t saddr_len = sizeof(saddr);
  memset(&saddr, 0x00, sizeof(saddr));
  len = recvfrom(sockfd, buf, len, 0, (struct sockaddr *)&saddr, &saddr_len);
  if(len == -1) {
    return -1;
  }
  if(addr) strcpy(addr, (char *)inet_ntoa(saddr.sin_addr));
  if(port) *port = ntohs(saddr.sin_port);
  return len;  
}

int UdpMCastRevInit(const char *localAddr, const char *mcastAddr, int mcastPort);
int mbsSetMcastIF(int sockfd, char *interface_addr);
int mbsSetMcastTTL(int sockfd, int ttl);
int mbsSetMcastLOOP(int sockfd, int loop);
int mbsAddMemberIP(int sockfd, char *multiaddr);
int mbsDropMemberIP(int sockfd, char *multiaddr);


