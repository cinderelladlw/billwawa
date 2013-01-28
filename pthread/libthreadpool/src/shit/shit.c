#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
#define MAX 202
#define INF 0x3f3f3f3f
int dis[MAX][MAX],vis[MAX],key[MAX];
char s[MAX][50];  //  存放地名的
int n,pos;
int finddes(char a[])
{
    for(int i=1;i<=pos;i++)
     if(strcmp(s[i],a)==0)
        return i;
   strcpy(s[++pos],a);
   return pos;
}
void Dijkstra(int end)
{
    int min,i,j,k;
    for(i=1;i<=pos;i++)
    {
        vis[i]=0;
        key[i]=dis[end][i];
    }
    vis[end]=1;
    key[end]=0;
    for(i=1;i<=pos;i++)
    {
        min=INF;
        k=-1;
        for(j=1;j<=pos;j++)
         if(vis[j]==0 && key[j]<min)
         {
             k=j;
             min=key[j];
         }
        vis[k]=1;
        for(j=1;j<=pos;j++)
         if(vis[j]==0 && key[j]>key[k]+dis[k][j] && dis[k][j]<INF)
           key[j]=key[k]+dis[k][j];
    }
}
int main()
{
    int n,i,j,num;
    int temi,temj,sx,ex;
    char start[50],end[50];
    while(scanf("%d",&n)!=EOF && n!=-1)
    {
        memset(dis,INF,sizeof(dis));
        memset(s,0,sizeof(s));
        pos=0;
        cin>>start>>end;
        sx=finddes(start);
        ex=finddes(end);
        for(i=0;i<n;i++)
        {
          cin>>start>>end>>num;
          temi=finddes(start);
          temj=finddes(end);
          dis[temi][temj]=dis[temj][temi]=num;
        }
        if(sx==ex)
            printf("0\n");
        else
        {
          Dijkstra(sx);
          if(key[ex]==INF)
             printf("-1\n");
           else
             printf("%d\n",key[ex]);
        }

    }
    return 0;
}

