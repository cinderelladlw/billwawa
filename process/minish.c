/* mshell.c */
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

void do_cd(char *argv[]);
void execute_new(char *argv[]);

main()
{
	char *cmd=(void *)malloc(256*sizeof(char));
	char *cmd_arg[10];
	int cmdlen,i,j,tag;

	do{
		/* 初始化cmd */
		for(i=0;i<255;i++) cmd[i]='\0';

		printf("-=Mini Shell=-*| ");
		fgets(cmd,256,stdin);

		cmdlen=strlen(cmd);
		cmdlen--;
		cmd[cmdlen]='\0';

		/* 把命令行分解为指针数组cmd_arg */
		for(i=0;i<10;i++) cmd_arg[i]=NULL;
		i=0; j=0; tag=0;
		while(i<cmdlen && j<10){
			if(cmd[i]==' '){
				cmd[i]='\0';
				tag=0;
			}else{
				if(tag==0)
					cmd_arg[j++]=cmd+i;
				tag=1;
			}
			i++;
		}
		
		/* 如果参数超过10个，就打印错误，并忽略当前输入 */
		if(j>=10 && i<cmdlen){
			printf("TOO MANY ARGUMENTS\n");
			continue;
		}
		
		/* 命令quit：退出Mini Shell */
		if(strcmp(cmd_arg[0],"quit")==0)
			break;

		/* 命令cd */
		if(strcmp(cmd_arg[0],"cd")==0){
			do_cd(cmd_arg);
			continue;
		}
		
		/* 外部命令或应用程序 */
		execute_new(cmd_arg);
	}while(1);
}

/* 实现cd的功能 */
void do_cd(char *argv[])
{
	if(argv[1]!=NULL){
		if(chdir(argv[1])<0)
			switch(errno){
			case ENOENT:
				printf("DIRECTORY NOT FOUND\n");
				break;
			case ENOTDIR:
				printf("NOT A DIRECTORY NAME\n");
				break;
			case EACCES:
				printf("YOU DO NOT HAVE RIGHT TO ACCESS\n");
				break;
			default:
				printf("SOME ERROR HAPPENED IN CHDIR\n");
			}
	}

}

/* 执行外部命令或应用程序 */
void execute_new(char *argv[])
{
	pid_t pid;

	pid=fork();
	if(pid<0){
		printf("SOME ERROR HAPPENED IN FORK\n");
		exit(2);
	}else if(pid==0){
		if(execvp(argv[0],argv)<0)
			switch(errno){
			case ENOENT:
				printf("COMMAND OR FILENAME NOT FOUND\n");
				break;
			case EACCES:
				printf("YOU DO NOT HAVE RIGHT TO ACCESS\n");
				break;
                        default:
                                printf("SOME ERROR HAPPENED IN EXEC\n");
			}
		exit(3);
	}else 
		wait(NULL);
}	

