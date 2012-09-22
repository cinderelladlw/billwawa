#ifndef __socket_h_
#define __socket_h_
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <net/if.h>
#include <sys/ioctl.h>

int GetLocalIP(char *ip, const chr *netdev);
int ParseDNS(char *ip, const char *dns);
//TCP
int TcpSelect(int ilFd, long iSeconds);
int TcpListen(int port);
int TcpListenX(char *iP, int port);
int TcpConnect(const char *addr, int port);
int TcpConnectX(char *alIp, int ilPort, long ilTime);
int TcpAccept(int sockfd, char *addr, int *port);
int TcpSoLinger(int sockfd, int on ,int linger);
int TcpNodelay(int sockfd, int on);

int TcpRecv(int sockfd, char *buf, int len ,int tiemout);
int TcpSend(int sockfd, const char *buf, int len);
int TcpRead(int sockfd, char *buf, int len, int lenlen, int timeout);
int TcpWrite(int sockfd, const char *buf, int len, int lenlen);
//UDP
int UdpInit(int port);
int UdpMCastRevInit(const char *localAddr, const char *mcastAddr, int mcastPort);
int UdpSendTo(int sockfd, const char *buf, int len, const char *addr, int port);
int UdpRecvFrom(int sockfd, char *buf, int len, char *addr, int *port);
int mbsSetMcastIF(int sockfd, char *interface_addr);
int mbsSetMcastTTL(int sockfd, int ttl);
int mbsSetMcastLOOP(int sockfd, int loop);
int mbsAddMemberIP(int sockfd, char *multiaddr);
int mbsDropMemberIP(int sockfd, char *multiaddr);


#endif

