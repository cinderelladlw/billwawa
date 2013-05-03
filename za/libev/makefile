CC=gcc
#FLAGS=-I. -I/home/lengzijian/c/libev/libev-4.11 
#LDFLAGS=-L/usr/lib -L/home/lengzijian/c/libev/libev-4.11/.libs -lev -Wall

OBJECTS=server.o
ALL_BIN=server

all:$(ALL_BIN) 

$(ALL_BIN):$(OBJECTS) 
	$(CC) -o $@ $^ -lev


%.o:%.c
	$(CC) -c $< 

clean:
	rm -fr $(OBJECTS)
	rm -fr $(ALL_BIN)
