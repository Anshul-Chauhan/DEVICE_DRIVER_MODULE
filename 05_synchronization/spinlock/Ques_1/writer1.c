#include <stdio.h>
#include <fcntl.h>

int main()
{
    int fd;
    char Ubuf[] = "Hello! this is the data from writer 1.";

    fd = open("/dev/SpinCharDevice1", O_RDWR, 0777);
    if(fd < 0)
    {
        printf("Error opening Device.\n");
        exit(1);
    }
    
    write(fd, Ubuf, sizeof(Ubuf));
    printf("Data from writer 1 has written into the kernel buffer successfully (Hello! this is the data from writer 1).\n");

    close(fd);
    return 0;
}

