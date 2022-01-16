#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
    int fd4, num1, num2;
    printf("Enter two numbers: \n");
    scanf("%d", &num1);
    scanf("%d", &num2);
    char Ubuf1[16] = "";
    char Ubuf2[16] = "";
    char Kbuf[100];
    sprintf(Ubuf1, "%d", num1);
    sprintf(Ubuf2, "%d", num2);
    fd4 = open("/dev/div", O_RDWR, 0777);
    if(fd4 < 0)
    {
        printf("Error opening Device.\n");
        exit(1);
    }
    write(fd4, Ubuf1, sizeof(int));
    write(fd4, Ubuf2, sizeof(int));
    read(fd4, Kbuf, 80);
    printf("Data read from kernel i.e division of %d from %d : \n%s\n", num1, num2, Kbuf);
    close(fd4);  
    
    return 0;
}