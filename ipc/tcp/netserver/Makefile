#头文件
ORACLEINC = -I $(ORACLE_HOME)/precomp/public -I $(ORACLE_HOME)/rdbms/public

INCLUDE = $(ORACLEINC)
#库文件
ORACLELIB = -L $(ORACLE_HOME)/lib -lclntsh -lclient11

LIBS = $(ORACLELIB)
#编译命令
CC = gcc
AR = ar
ESQL = proc

#编译目标
#LIBOBJS = *.o
#CFLAGS=

#编译规则
.SUFFIXES: .pc .c .o
.pc.c:
	$(ESQL) $*.pc 
.c.o:
	$(CC) -c $*.c $(INCLUDE) $(CFLAGS)

all: lib exe
lib: libmbs.a
exe: cli

cli:cli.o
	$(CC) $@ $?

libmbs.a: $(LIBOBJS)
	$(AR) -rv $@ $?

clean:
	rm -f *.lis *.o
