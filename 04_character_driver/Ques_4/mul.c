#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
    int fd3, num1, num2;
    printf("Enter two numbers: \n");
    scanf("%d", &num1);
    scanf("%d", &num2);
    char Ubuf1[16] = "";
    char Ubuf2[16] = "";
    char Kbuf[100];
    sprintf(Ubuf1, "%d", num1);
    sprintf(Ubuf2, "%d", num2);
    fd3 = open("/dev/mul", O_RDWR, 0777);
    if(fd3 < 0)
    {
        printf("Error opening Device.\n");
        exit(1);
    }
    write(fd3, Ubuf1, sizeof(int));
    write(fd3, Ubuf2, sizeof(int));
    read(fd3, Kbuf, 80);
    printf("Data read from kernel i.e multiplication of %d and %d : \n%s\n", num1, num2, Kbuf);
    close(fd3);  
    
    return 0;
}