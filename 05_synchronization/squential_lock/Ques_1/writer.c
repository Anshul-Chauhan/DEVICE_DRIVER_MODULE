#include <stdio.h>
#include <fcntl.h>

int main()
{
    int fd;
    char Ubuf[] = "Hello! I am writting data into the kernel buffer.";

    fd = open("/dev/SeqnCharDevice1", O_RDWR, 0777);
    if(fd < 0)
    {
        printf("Error opening Device.\n");
        exit(1);
    }
    
    write(fd, Ubuf, sizeof(Ubuf));
    printf("Data from writer has written into the kernel buffer successfully.\n");

    close(fd);
    return 0;
}

