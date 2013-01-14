#include <stdio.h>
#include <setjmp.h>
void subroutine(void);
void subroutine_2(void);

jmp_buf jumper;

int main()
{
    int value;
    int i = 0;
    value = setjmp(jumper);   /* 设置jump点,初始化jumper,返回值0赋给value, */
    i++;
    printf("执行第[%d]次:value = [%d]: >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n",i,value);
    if(value == 0)
    {
        printf("[1]About to call subroutine.....\n");
        subroutine();  /* 调转到subroutine()函数 */
        printf("Never go this....\n");
    }
    else if(value == 1)
    {
        printf("[2]About to call subroutine.....\n");
        subroutine_2();  /* 调转到subroutine_2()函数 */
        printf("Never go this....\n");
    }
    else
    {
        printf("[3]Never go this....\n");
    }

    return 0;
}

void subroutine(void)
{   

    /* 调转到jumper初始化的地方,即setjmp(jumper)处,并将1赋给set(jumper) */
    longjmp(jumper,1);
    return;
}

void subroutine_2(void)
{   

    /* 调转到jumper初始化的地方,即setjmp(jumper)处,并将3赋给set(jumper) */
    longjmp(jumper,3);
    return;
}

