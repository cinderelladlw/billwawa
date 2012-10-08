#日志库函数 makefile
#头文件
INCL = -I$(MBS_HOME)/xpe/include

#类库文件路径
SYS_LIBS = -lpthread

AR = ar -r
CFLAGS = -g DOS_LINUX

all:lib 

lib:libLog.a

libLog.a:Log.o
	$(AR) -cv $@ Log.o

.SUFFIXES:.c .o .h .tpye

.c.o:
	$(CC) -c -fpic $*.c $(INCL)
	@echo "编译 $*.c 成功"
clean:
	rm -rf *.o
