#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h> 

int main()
{
    char key;
    FILE *stream;/*����ָ��*/
    
    printf("Please input a letter.\n");
    key=getchar();/*����һ���ַ�*/
    
    if((stream=fopen("test","w"))==(FILE*)0)/*������һ���ļ���ϵ����,���ж��Ƿ�ɹ�*/
    {
        fprintf(stderr,"Error opening file.\n");
        exit(1);
    }
    /*���������趨Ϊ�л���*/

    
    setlinebuf(stream);

    /*����Ӧ�Ļ��������*/
    
    __fpurge(stream);
    
    
    /*�����Ķ�д����*/
    fprintf(stream,"The letter that you input is %c.\n",key);
    /*�ڳ������ǰ�ر���,���жϲ����Ƿ�ɹ�*/
    if((fclose(stream))==EOF)
    {
        fprintf(stderr,"Error closing file!\n");
        exit(1);
    }
    
    exit(0);
}
