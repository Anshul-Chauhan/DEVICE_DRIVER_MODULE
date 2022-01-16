#include <stdio.h>
#include <fcntl.h>

int main()
{
    int fd, num1, num2, num3;
    char Ubuf1[20] = "";
    char Ubuf2[20] = "";
    char Ubuf3[20] = "";
    
    fd = open("/dev/ComplCharDevice1", O_RDWR, 0777);
    if(fd < 0)
    {
        printf("Error opening Device.\n");
        exit(1);
    }
    printf("Enter number 1:");
    scanf("%d", &num1);
    sprintf(Ubuf1, "%d", num1);
    write(fd, Ubuf1, sizeof(Ubuf1));
    
    printf("Enter number 2:");
    scanf("%d", &num2);
    sprintf(Ubuf2, "%d", num2);
    write(fd, Ubuf2, sizeof(Ubuf2));
    
    printf("Enter number 3:");
    scanf("%d", &num3);
    sprintf(Ubuf3, "%d", num3);
    write(fd, Ubuf3, sizeof(Ubuf3));
    printf("Data from writer has successfully written into the kernel buffer.\n");

    close(fd);
    return 0;
}

