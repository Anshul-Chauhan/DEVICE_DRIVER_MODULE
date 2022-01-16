#include <stdio.h>
#include <fcntl.h>

int main()
{
    int fd;
    char Ubuf[] = "Data writing into kernel space from user space.";
    char Kbuf[100];
    fd = open("/dev/MyCharDevice3", O_RDWR, 0777);
    if(fd < 0)
    {
        printf("Error opening Device.\n");
        exit(1);
    }
    write(fd, Ubuf, sizeof(Ubuf));
    read(fd, Kbuf, 80);
    printf("Data read from kernel: \n'%s'\n", Kbuf);
    close(fd);
    
    return 0;
}