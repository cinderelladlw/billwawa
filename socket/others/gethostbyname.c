#include <stdio.h>
#include <string.h>
#include <netdb.h>

int main(int argc, char **argv)
{
  char host[100];
  memset(host, 0x00, 100);
  memcpy(host, argv[1], 100); 
  struct hostent *ht = NULL;
  
  ht = gethostbyname(host);
  if (ht) {
    int i = 0;
    printf("get the host:%s\n", host);
    printf("name:%s\n", ht -> h_name);
    printf("type:%s\n", (ht -> h_addrtype == AF_INET)?"AF_INET":"AF_INET6");
    printf("length:%d\n", ht -> h_length);
    for (i = 0; ; i++) {
      if (ht -> h_addr_list[i] != NULL) {
        printf("IP:%s\n", (char *)inet_ntoa((struct in_addr *)(ht-> h_addr_list[i])));
        //printf("IP:%s\n", inet_ntoa(ht -> h_addr_list[i]));
      } else {
        break;
      }
    } 
    for (i = 0; ; i++) {
      if (ht -> h_aliases[i] != NULL) {
        printf("alias %d:%s\n", i, ht -> h_aliases[i]); 
      } else {
        break;
      } 
    }
  }
  return 0;
}
