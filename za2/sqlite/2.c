#include <stdio.h>
#include <sqlite3.h>

static sqlite3 *db;
char *zErrMsg = 0;
static char *dbpath;
int rc;
int i;

static int callback(void *NotUsed, int a, char **ar, char **azColName){
  int i;
  for(i=0; i<a; i++){
    printf("%s = %s\n", azColName[i], ar[i] ? ar[i] : "NULL");
  }
  printf("\n");
  return 0;
}

static sqlite3 *opendb(char *dbp) {
  if(sqlite3_open(dbp, &db) != SQLITE_OK) {
    sqlite3_close(db);
    printf("open db error\n");
  }
  return db;
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
  

int main(int argc, char **argv){
  int j = atoi(argv[3]);
  int k = atoi(argv[4]);
  if( argc != 5 ){
    fprintf(stderr, "Usage: %s DATABASE SQL-STATEMENT TIMES transactionsize \n", argv[0]);
    return(1);
  }
  /*
  rc = sqlite3_open(argv[1], &db);
  if( rc ){
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return(1);
  }
  */
  dbpath = argv[1];
  sqlite3 *db2;
  db2 = opendb(dbpath); 
  while(j >= k) {
    committransaction(argv[2], k);
    j = j - k; 
  }
  committransaction(argv[2], j);
  

  sqlite3_close(db);
  return 0;
}
