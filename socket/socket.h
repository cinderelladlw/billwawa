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

int GetLocalIp(char *ip, const chr *netdev);
int ParseDNS(char *ip, const char *dns);
#endif

