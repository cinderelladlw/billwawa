#include "config.h" 

static int sb = 0;

static int callback(void *NotUsed, int a, char **ar, char **azColName){
  int i;
  for(i=0; i<a; i++){
    printf("%s = %s\n", azColName[i], ar[i] ? ar[i] : "NULL");
    if(i == 0) {
      strcpy(sxx[sb].dllname, ar[i]?ar[i]:"NULL"); 
    } else {
      strcpy(sxx[sb].funcname, ar[i]?ar[i]:"NULL"); 
      sb++;
    }
  }
  return 0;
}

static int committransaction(char *commitsql, int commitnumber) {
  rc = sqlite3_exec(db, "begin immediate", 0, 0, &zErrMsg);
  for(i = 0; i < commitnumber; i++) { 
    rc = sqlite3_exec(db, commitsql, callback, 0, &zErrMsg);
    if( rc!=SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
    }
  }
  rc = sqlite3_exec(db, "commit", 0, 0, &zErrMsg);
}

int readconfig()
{ 
  rc = sqlite3_open("mbs.db", &db);
  if (rc) {
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return -1;
  }
  committransaction("select * from config", 1);
  sqlite3_close(db);
  return sb;
}


/*
int main()
{
  readconfig();
  return 0;
}
int main(int argc, char **argv)
{
  int j = atoi(argv[3]);
  int k = atoi(argv[4]);
  if( argc != 5 ){
    fprintf(stderr, "Usage: %s DATABASE SQL-STATEMENT TIMES transactionsize \n", argv[0]);
    return(1);
  }
  rc = sqlite3_open(argv[1], &db);
  if( rc ){
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return(1);
  }
  while(j >= k) {
    committransaction(argv[2], k);
    j = j - k; 
  }
  committransaction(argv[2], j);
  

  sqlite3_close(db);
  return 0;
}
*/
