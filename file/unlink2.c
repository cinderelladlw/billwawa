#include<unistd.h>
#include<stdio.h>
int main(void)
{
FILE *fp = fopen("junk.jnk","w");
int status;
fprintf(fp,"junk");
status = access("junk.jnk",0);
if (status == 0)
printf("File exists\n");
else
printf("File doesn't exist\n");
fclose(fp);

unlink("junk.jnk");
status = access("junk.jnk",0);
if (status == 0)
printf("File exists\n");
else
printf("File doesn't exist\n");
return 0;
}
