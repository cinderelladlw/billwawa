CC:= gcc
LD:= ld
CFLAGS:=
LDFLAGS:= -fPIC -shared

SOURCE:= $(wildcard ./*.c)
OBJ:= $(patsubst %.c,%.o,$(SOURCE))

OLP_INC=-I../include

TARGET_LIB := liblog.so

all:$(OBJS)
	echo $(OBJ)
	$(CC) $(SOURCE) $(LDFLAGS) -o $(TARGET_LIB) $(OLP_INC)
%.o:%.c
	@echo Compiling $< ...

.PHONY: clean

clean:
	rm *.so *.o -rf
