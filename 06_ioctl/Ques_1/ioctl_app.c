#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <asm/ioctl.h>
#include "ioctl.h"

struct DefaultData
{
    int BaudRate;
    int StopBits;
    int Parity;
};

int main()
{
    int fd, result, BAUD_RATE = 9600, STOP_BITS = 8;
    struct DefaultData ToSend = {9800, 1, 0};
    char Ubuf[] = "This is the data of user buffer of ioctl application sending to kernel buffer.";
    char Kbuf[100];
    
    fd = open("/dev/MyIOCTLdevice", O_RDWR, 0777);
    if(fd < 0)
    {
        printf("Error opening device.\n");
        exit(1);
    }

    result = ioctl(fd, SET_BAUD_RATE, &BAUD_RATE);
    if(result < 0)
    {
        printf("IOCTL error.\n");
        return (-1);
    }
    printf("Baud Rate confirmation: %d\n", BAUD_RATE);

    ioctl(fd, SET_NO_OF_STOP_BITS, &STOP_BITS);
    ioctl(fd, SET_DIRECTION_WRITE, NULL);
    ioctl(fd, DEFAULT_DATA, &ToSend);

    write(fd, Ubuf, sizeof(Ubuf));
    read(fd, Kbuf, sizeof(Kbuf));
    printf("The data read from the kernel: '%s'\n", Kbuf);
    close(fd);
    return 0;
}