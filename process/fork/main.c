#include <stdio.h>

int main(int argc, char **argv, char *envp[])
{
        printf("\n### ARGC ###\n%d\n", argc);
	printf("\n### ARGV ###\n");
	while(*argv)
		printf("%s\n", *(argv++));
	printf("\n### ENVP ###\n");
	while(*envp)
		printf("%s\n", *(envp++));
	return 0;
}
