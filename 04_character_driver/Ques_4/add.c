#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
    int fd1, num1, num2;
    printf("Enter two numbers: \n");
    scanf("%d", &num1);
    scanf("%d", &num2);
    char Ubuf1[16] = "";
    char Ubuf2[16] = "";
    char Kbuf[100];
    sprintf(Ubuf1, "%d", num1);
    sprintf(Ubuf2, "%d", num2);
    fd1 = open("/dev/add", O_RDWR, 0777);
    if(fd1 < 0)
    {
        printf("Error opening Device.\n");
        exit(1);
    }
    write(fd1, Ubuf1, 16);
    write(fd1, Ubuf2, 16);
    read(fd1, Kbuf, 80);
    printf("Data read from kernel i.e addition of %d and %d : \n%s\n", num1, num2, Kbuf);
    close(fd1);
    
    return 0;
}