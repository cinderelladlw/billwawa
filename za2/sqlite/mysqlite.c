#include <stdio.h>
#include <stdlib.h> //exit等函数的声明
#include <sqlite3.h>

int displaycb(void *para,int n_column,char **column_value,char **column_name);

int inquire_Usecb(sqlite3 *db);

int inquire_nocb(sqlite3 *db);

int createTable(sqlite3 *db);

int insertRecord(sqlite3 *db);

int deleteRecord(sqlite3 *db);


//回调函数 每一条记录执行一次
int displaycb(void *para,int n_column,char **column_value,char **column_name)
{
	int i = 0;
	printf("Total column is %d\n",n_column);
	for(i = 0;i<n_column;i++){
		printf("字段名: %s---->字段值:%s\n",column_name[i],column_value[i]);
	}
	printf("==========================\n");
	return 0;
}
//使用回调函数的查询
int inquire_Usecb(sqlite3 *db)
{
	char *sql;
	char *zErrMsg;
	sql = "select * from 'SensorData';";
	if(SQLITE_OK != sqlite3_exec(db,sql,displaycb,NULL,&zErrMsg)){
		printf("operate failed: %s\n",zErrMsg);
	}
	return 0;
}
//不使用回调函数的查询
int inquire_nocb(sqlite3 *db)
{
	int nrow = 0,ncolumn = 0;
	char **azResult=0;
	int i = 0;
	char *sql;
	char *zErrMsg;
	sql = "SELECT * FROM SensorData";
	if(SQLITE_OK != sqlite3_get_table(db,sql,&azResult,&nrow,&ncolumn,&zErrMsg)){
		printf("operate failed: %s\n",zErrMsg);
	}

	printf("row:%d column = %d\n",nrow,ncolumn);
	printf("The result of querying is :\n");
	for ( i = 0;i < ( nrow + 1) * ncolumn; i++)
		printf("azResult[%d] = %s\n",i,azResult[i]);
	sqlite3_free_table(azResult);
	return 0;
}
//创建表函数
int createTable(sqlite3 *db)
{
	char *zErrMsg = 0;
	char *sql = "CREATE TABLE SensorData(ID INTEGER PRIMARY KEY,SensorID INTEGER,SiteNum INTERER,Time VARCHAR(12),SensorParameter REAL);";
	if(SQLITE_OK != sqlite3_exec(db,sql,0,0,&zErrMsg)){
		printf("operate failed: %s\n",zErrMsg);
	}
}
//插入数据函数
int insertRecord(sqlite3 *db)
{
	char *sql;
	char *zErrMsg;
	sql = "INSERT INTO 'SensorData' VALUES(NULL,101,261,'20100314',18.9);";
	if(SQLITE_OK != sqlite3_exec(db,sql,0,0,&zErrMsg)){
		printf("operate failed: %s\n",zErrMsg);
	}

	sql = "INSERT INTO 'SensorData' VALUES(NULL,369,281,'20100616',113);";
	if(SQLITE_OK != sqlite3_exec(db,sql,0,0,&zErrMsg)){
		printf("operate failed: %s\n",zErrMsg);
	}

	sql = "INSERT INTO 'SensorData' VALUES(NULL,667,290,'20110315',27);";
	if(SQLITE_OK != sqlite3_exec(db,sql,0,0,&zErrMsg)){
		printf("operate failed: %s\n",zErrMsg);
	}

	sql = "INSERT INTO 'SensorData' VALUES(NULL,865,300,'20120616',323);";
	if(SQLITE_OK != sqlite3_exec(db,sql,0,0,&zErrMsg)){
		printf("operate failed: %s\n",zErrMsg);
	}

}
//删除数据函数
int deleteRecord(sqlite3 *db)
{
	char *sql;
	char *zErrMsg;
	char **azResult=0;
	int nrow = 0,ncolumn = 0;
	int i;
	sql = "DELETE FROM SensorData WHERE ID=4;";
	if(SQLITE_OK != sqlite3_exec(db,sql,0,0,&zErrMsg)){
		printf("operate failed: %s\n",zErrMsg);
	}

	sql = "SELECT * FROM SensorData;";
	if(SQLITE_OK != sqlite3_get_table(db,sql,&azResult ,&nrow,&ncolumn,&zErrMsg)){
		printf("operate failed: %s\n",zErrMsg);
	}
	printf("row:%d column:%d\n",nrow,ncolumn);
	printf("After deleting,the result of querying is :\n");
	for(i=0;i<(nrow+1)*ncolumn;i++)
		printf("azResult[%d] = %s\n",i,azResult[i]);
	sqlite3_free_table(azResult);
}
int main(void)
{
	sqlite3 *db = NULL;
	int rc;

	//打开指定的数据库文件
	rc = sqlite3_open("mydatabase.db",&db);
	if(rc){
		fprintf(stderr,"can't open database: %s\n",sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}else
		printf("You have opened a sqlite3 database successfully!\n");
	//创建表
	createTable(db);
	//插入记录
	insertRecord(db);
	//查询
	//使用sqlite3_get_table实现查询
	inquire_nocb(db);
	printf("ppppppppppppppppppppppppppppppppppp\n");
	//使用回调函数实现查询
	inquire_Usecb(db);
	//删除记录
	deleteRecord(db);
	//关闭数据库
	sqlite3_close(db);
	return 0;
}
