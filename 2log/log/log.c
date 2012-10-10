#include "log.h"

#define      LOG_FILE_PATH     "./test.log"



void  WriteLog(const char * Fmt,...)
{
	char  buffer[512] ;
	char  timebuf[64]  ;

 	//open the log file !
	 FILE * fp = NULL ;
	     if (!(fp = fopen(LOG_FILE_PATH,"a+")))
	     {
	     		 printf("can't open the LogFile!"); 
			 exit (1); 
	     } 

	time_t timep ;
	time(&timep) ;

	memset( timebuf,0,64 );
	int length = strlen( asctime(gmtime(&timep)) ) ;
	//delete the last '\n' letter !!
	strncpy(timebuf,asctime(gmtime(&timep)),length-1) ;	
	       
        va_list arg_ptr;

        va_start(arg_ptr, Fmt);

        vsprintf(buffer,Fmt,arg_ptr); 
	
        va_end(arg_ptr);
	
	fprintf(fp,"The time : %s  %s\n",timebuf,buffer) ;
	
	fclose(fp) ;
        
}


