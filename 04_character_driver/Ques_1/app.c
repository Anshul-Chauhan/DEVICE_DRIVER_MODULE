#include <stdio.h>
#include<stdio.h>
#include <fcntl.h>

int main()
{
    int fd;
    char Ubuf[] = "Data writing into kernel space from user space.";
    char Kbuf[100];
    fd = open("/dev/MyCharDevice1", O_RDWR, 0777);
    if(fd < 0)
    {
        printf("Error opening Device.\n");
        exit(1);
    }
    printf("Open functionality in the device driver has been executed.\n");
    close(fd);
    printf("Close functionality in the device driver has been executed.\n");
    return 0;
}