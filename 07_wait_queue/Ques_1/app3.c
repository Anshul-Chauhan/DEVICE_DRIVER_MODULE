#include <stdio.h>
#include <fcntl.h>

int main()
{
    int fd;
    char Ubuf[] = "Data from application 3, written successfully";

    fd = open("/dev/WaitCharDevice", O_RDWR, 0777);
    if(fd < 0)
    {
        printf("Error opening Device.\n");
        exit(1);
    }
    
    write(fd, Ubuf, sizeof(Ubuf));
    printf("Data from application 3 has written into the kernel buffer successfully.\n");

    close(fd);
    return 0;
}

