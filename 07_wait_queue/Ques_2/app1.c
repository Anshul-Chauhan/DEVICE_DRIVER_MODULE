#include <stdio.h>
#include <fcntl.h>

int main()
{
    int fd;
    char Ubuf[] = "Data from application 1, written successfully";

    fd = open("/dev/WaitCharDevice1", O_RDWR, 0777);
    if(fd < 0)
    {
        printf("Error opening Device.\n");
        exit(1);
    }
    printf("You can press 'ctrl+c' to kill the process as this wait queue is interruptible.\n");
    write(fd, Ubuf, sizeof(Ubuf));
    printf("Data from application 1 has written into the kernel buffer successfully.\n");

    close(fd);
    return 0;
}

