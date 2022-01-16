obj-m := spinl_driver1.o

KERNELDIR = /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

default:
		$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
		gcc -o writer1 writer1.c
		gcc -o writer2 writer2.c
		gcc -o writer3 writer3.c
		gcc -o reader reader.c

install:
		$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install

clean:
		$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
		rm writer1 writer2 writer3 reader
