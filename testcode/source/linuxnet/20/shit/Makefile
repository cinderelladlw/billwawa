obj-m := shit.o 
kernel_path=/lib/modules/`uname -r`/build
#内核路径 
all: 
	make -C $(kernel_path)  M=$(PWD) modules 
clean: 
	make -C $(kernel_path)  M=$(PWD) clean
