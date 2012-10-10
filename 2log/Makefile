CC=gcc
CFLAGS=-llog 
SRC=$(wildcard ./*.c)
STU_INC= -I./include

#OBJ=./usr/lib

TARGET= main

all:
	cd ./log;make
	cp ./log/liblog.so /usr/lib
	

	$(CC) -o $(TARGET) $(SRC)  $(STU_INC)  $(CFLAGS) 

clean:
	
	cd ./log;make clean
	rm -f main
