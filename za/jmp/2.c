#include <stdio.h>
#include <setjmp.h>
void subroutine(void);
void subroutine_2(void);

jmp_buf jumper;

int main()
{
    int value;
    int i = 0;
    value = setjmp(jumper);   /* ����jump��,��ʼ��jumper,����ֵ0����value, */
    i++;
    printf("ִ�е�[%d]��:value = [%d]: >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n",i,value);
    if(value == 0)
    {
        printf("[1]About to call subroutine.....\n");
        subroutine();  /* ��ת��subroutine()���� */
        printf("Never go this....\n");
    }
    else if(value == 1)
    {
        printf("[2]About to call subroutine.....\n");
        subroutine_2();  /* ��ת��subroutine_2()���� */
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

    /* ��ת��jumper��ʼ���ĵط�,��setjmp(jumper)��,����1����set(jumper) */
    longjmp(jumper,1);
    return;
}

void subroutine_2(void)
{   

    /* ��ת��jumper��ʼ���ĵط�,��setjmp(jumper)��,����3����set(jumper) */
    longjmp(jumper,3);
    return;
}

