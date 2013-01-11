#include <stdio.h>

int main(void)
{
    int  i;
    //这是字符数组赋初值的方法，维数：4Ｘ2
    char cArr[][2] = {{'Q','U'},
                     {'A','N'},
                     {'X','U'},
                     {'E','\0'}};
    //这是字符串数组赋初值的方法，维数：4Ｘ3
    char sArr[][3] = {"qu","an","xu","e"};
    //用sizeof()求长度
    for (i=0; i<4; i++) {
        printf("%d: %d  %d\n", i, sizeof(cArr[i]), sizeof(sArr[i]));
        printf("[%s] [%s]\n", cArr[i], sArr[i]);
    }
    return 0;
}
