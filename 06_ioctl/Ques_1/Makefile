obj-m := ioctl_driver.o

KERNELDIR = /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

default:
		$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
		gcc -o ioctl_app ioctl_app.c

install:
		$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install

clean:
		$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
		rm ioctl_app
