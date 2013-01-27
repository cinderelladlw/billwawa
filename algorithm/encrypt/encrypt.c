#include <stdio.h>
#define SIZE 13
char encrypt(char ch, char key[],int len)
{
	static int i = 0;
	int j;
	char key1 = 0;
	for(j = 0; j < 8; j++) {
		key1 >>= 1;
		i = (i + j) % len;
		if(key[i+j] == 1) {
			key1 |= 0x80; 
		}
	}
	return ch ^ key1;
}

int main()
{
	char key[SIZE] = {0,1,1,0,0,1,0,0,0,1,1,1,0};
	int ch;
	FILE *pf = fopen("SuperFC","r+");
	while((ch = fgetc(pf)) != EOF)
	{
		ch = encrypt(ch,key,13);
		fseek(pf, -1, SEEK_CUR);
		fputc(ch,pf);
		fflush(pf);
	}
	fclose(pf);

	return 0;
}
