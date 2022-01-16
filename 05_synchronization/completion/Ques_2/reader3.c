#include <stdio.h>
#include <fcntl.h>

int main()
{
    int fd;
    char Ubuf[120];

    fd = open("/dev/ComplCharDevice2", O_RDWR, 0777);
    if(fd < 0)
    {
        printf("Error opening Device.\n");
        exit(1);
    }
    
    read(fd, Ubuf, 120);
    printf("Data read from kernel by reader 3: '%s'\n", Ubuf);

    close(fd);
    return 0;
}

