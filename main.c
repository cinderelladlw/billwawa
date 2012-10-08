#include <stdio.h> 
     
int main()  
{  
        // 文件指针和保存输入的字符串  
        FILE *fp = NULL;  
        char str[100] = "";  
           
           
        // 以可写方式打开文件  
        if(NULL==(fp = fopen("test.txt","w")))  
        {   
            printf("cannot open the file.\n");  
            exit(0);  
        }  
     
        // 提示用户输入  
        printf("please input a string:\n");  
        do  
        {  
            // 判断输入是否结束  
            gets(str);  
            if('!'==str[0])  
                break;  
            // 写入文件  
            fputc(str,fp);  
        }while(1);  
           
        // 关闭文件  
        fclose(fp);  
    }  
