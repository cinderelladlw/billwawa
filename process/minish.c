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
		/* ��ʼ��cmd */
		for(i=0;i<255;i++) cmd[i]='\0';

		printf("-=Mini Shell=-*| ");
		fgets(cmd,256,stdin);

		cmdlen=strlen(cmd);
		cmdlen--;
		cmd[cmdlen]='\0';

		/* �������зֽ�Ϊָ������cmd_arg */
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
		
		/* �����������10�����ʹ�ӡ���󣬲����Ե�ǰ���� */
		if(j>=10 && i<cmdlen){
			printf("TOO MANY ARGUMENTS\n");
			continue;
		}
		
		/* ����quit���˳�Mini Shell */
		if(strcmp(cmd_arg[0],"quit")==0)
			break;

		/* ����cd */
		if(strcmp(cmd_arg[0],"cd")==0){
			do_cd(cmd_arg);
			continue;
		}
		
		/* �ⲿ�����Ӧ�ó��� */
		execute_new(cmd_arg);
	}while(1);
}

/* ʵ��cd�Ĺ��� */
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

/* ִ���ⲿ�����Ӧ�ó��� */
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

