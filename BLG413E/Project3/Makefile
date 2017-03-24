obj-m := clumsy.o
all: 
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
