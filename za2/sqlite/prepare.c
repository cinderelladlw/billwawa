#include <stdio.h>
#include <sqlite3.h>

int main( int argc, char **argv )
{
        sqlite3 *db;
        sqlite3_stmt * stmt;
        const char *zTail;
        //�����ݿ�
        int r = sqlite3_open("mysqlite.db",&db);
        if(r){
                printf("%s",sqlite3_errmsg(db));
        }
        //����Table
        sqlite3_prepare(db,
                "CREATE TABLE players ( ID INTEGER PRIMARY KEY, name TEXT, age INTERER );",
                -1,&stmt,&zTail);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        //��������
        sqlite3_prepare(db,
                "INSERT INTO players (name,age) VALUES(?,?);",
                -1,&stmt,&zTail);
        char str[] = "Kevin";
        int n = 23;
        sqlite3_bind_text(stmt,1,str,-1,SQLITE_STATIC);
        sqlite3_bind_int(stmt,2,n);
        r = sqlite3_step(stmt);
        if( r!=SQLITE_DONE){
                printf("%s",sqlite3_errmsg(db));
        }
        sqlite3_reset(stmt);
        //����ڶ�������
        char str2[] = "Jack";
        int n2 = 16;
        sqlite3_bind_text(stmt,1,str2,-1,SQLITE_STATIC);
        sqlite3_bind_int(stmt,2,n2);
        r = sqlite3_step(stmt);
        if( r!=SQLITE_DONE){
                printf("%s",sqlite3_errmsg(db));
        }
        sqlite3_finalize(stmt);
        //��ѯ��������
        sqlite3_prepare(db,
                "SELECT ID, name, age FROM players ORDER BY age;",
                -1,&stmt,&zTail);
        r = sqlite3_step(stmt);
        int number;
        int id;
        const unsigned char * name;
        //while( r == SQLITE_ROW ){
                id = sqlite3_column_int( stmt, 0 );
                name = sqlite3_column_text( stmt,1 );
                number = sqlite3_column_int( stmt, 2 );
                printf("ID: %d  Name: %s  Age: %d \n",id,name,number);
                sqlite3_step(stmt);
       // }
        sqlite3_finalize(stmt);
        //�ر����ݿ�
        sqlite3_close(db);
        return 0;
} 
