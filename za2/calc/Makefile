all: calc adder.so suber.so muler.so diver.so
	@mv adder.so suber.so muler.so diver.so ~/.libs/
calc: calc.c parseconf.c
	gcc `pkg-config --cflags --libs glib-2.0`\
		`pkg-config --cflags --libs xml2`\
		-ldl -g -o calc calc.c parseconf.c
adder.so: adder.o
	gcc -shared -lc -o adder.so adder.o
adder.o: adder.c
	gcc -c -fpic adder.c
suber.so: suber.o
	gcc -shared -lc -o suber.so suber.o
suber.o: suber.c
	gcc -c -fpic suber.c
muler.so: muler.o
	gcc -shared -lc -o muler.so muler.o
muler.o: muler.c
	gcc -c -fpic muler.c
diver.so: diver.o
	gcc -shared -lc -o diver.so diver.o
diver.o: diver.c
	gcc -c -fpic diver.c

clean:
	rm -f *.o
	rm -f *.so
