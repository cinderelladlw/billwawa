#include<stdio.h>
#include<string.h>

char str[1000];
char ch(char c)
{
    if(c>=97&&c<=122)
    c-=32;
    return c;
}
int main()
{
    int i,l;
    scanf("%s",str);
    l=strlen(str);
    for(i=0;i<l;i+=2)
    str[i]=ch(str[i]);
    printf("%s\n",str);
    return 0;
}
