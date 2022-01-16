obj-m := wait_queue.o

KERNELDIR = /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

default:
		$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
		gcc -o app1 app1.c
		gcc -o app2 app2.c
		gcc -o app3 app3.c
		gcc -o app4 app4.c
		gcc -o app5 app5.c	

install:
		$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install

clean:
		$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
		rm app1 app2 app3 app4 app5
