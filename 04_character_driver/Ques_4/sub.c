#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
    int fd2, num1, num2;
    printf("Enter two numbers: \n");
    scanf("%d", &num1);
    scanf("%d", &num2);
    char Ubuf1[16] = "";
    char Ubuf2[16] = "";
    char Kbuf[100];
    sprintf(Ubuf1, "%d", num1);
    sprintf(Ubuf2, "%d", num2);
    fd2 = open("/dev/sub", O_RDWR, 0777);
    if(fd2 < 0)
    {
        printf("Error opening Device.\n");
        exit(1);
    }
    write(fd2, Ubuf1, sizeof(int));
    write(fd2, Ubuf2, sizeof(int));
    read(fd2, Kbuf, 80);
    printf("Data read from kernel i.e division of %d from %d : \n%s\n", num1, num2, Kbuf);
    close(fd2);  
    return 0;
}