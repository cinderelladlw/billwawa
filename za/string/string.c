#include <stdio.h>

int main(void)
{
    int  i;
    //�����ַ����鸳��ֵ�ķ�����ά����4��2
    char cArr[][2] = {{'Q','U'},
                     {'A','N'},
                     {'X','U'},
                     {'E','\0'}};
    //�����ַ������鸳��ֵ�ķ�����ά����4��3
    char sArr[][3] = {"qu","an","xu","e"};
    //��sizeof()�󳤶�
    for (i=0; i<4; i++) {
        printf("%d: %d  %d\n", i, sizeof(cArr[i]), sizeof(sArr[i]));
        printf("[%s] [%s]\n", cArr[i], sArr[i]);
    }
    return 0;
}
