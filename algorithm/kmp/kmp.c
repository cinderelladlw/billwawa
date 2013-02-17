#include <stdio.h>
#include <string.h>

void getNext(char *p, int *next);

int kmp(char *s, char *p)
{
  int next[100];
  int i,j;
  i = 0;
  j = 0;
  getNext(p, next);
  int sx;
  for(sx = 0; sx < 100; sx ++)
    printf("next[%d]:%d\n", sx, next[sx]);
  while(i < strlen(s)) {
    if(j == -1 || s[i] == p[j]) {
      i++;
      j++;
    }
    else {
      j = next[j];
    }
    if(j == strlen(p))
      return i - strlen(p);
  }
  return -1;
}

void getNext(char *p, int *next)
{
  int j,k;
  next[0] = -1;
  j = 0;
  k = -1;
  while(j < strlen(p) - 1) {
    if(k == -1 || p[j] == p[k]) {
      j++;
      k++;
      next[j] = k;
    }
    else {
      k = next[k];
    }
  }
}

int main()
{
  char *a = "helloworworworldsxsds";
  char *b = "worworld";
  int j = kmp(a, b);
  printf(":%d\n", j);
  return 0;

}

#if 0
//another getNext

void getNext(char *p,int *next)
{
    int i,j,temp;
    for(i=0;i<strlen(p);i++)
    {
        if(i==0)
        {
            next[i]=-1;     //next[0]=-1
        }
        else if(i==1) 
        {
            next[i]=0;      //next[1]=0
        }
        else
        {
            temp=i-1;
            for(j=temp;j>0;j--)
            {
                if(equals(p,i,j))
                {
                    next[i]=j;   //找到最大的k值
                    break;
                }
            }
            if(j==0)
                next[i]=0;
        }
    }
}

bool equals(char *p,int i,int j)     //判断p[0...j-1]与p[i-j...i-1]是否相等  
{
    int k=0;
    int s=i-j;
    for(;k<=j-1&&s<=i-1;k++,s++)

    {
        if(p[k]!=p[s])
            return false;
    }
    return true;
}

void GetNext(char *t,int next[])
{  
  int i,j=0;
  next[1]=0;        
  for(int i=2;i<=t[0];i++) {     
    j=next[i-1];                  //在next数组还没构造好的情况下就用了，有点递归的意思
    while(t[i-1]!=t[j]&& j>0 )
    j=next[j] ;                   //递推计算,不断地找恰当的位置
    if(t[i-1]==t[j]) next[i]=j+1;
    else next[i]=1;  
  }   
}
#endif
