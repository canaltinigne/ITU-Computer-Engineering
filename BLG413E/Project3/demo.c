#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<sys/ioctl.h>

#include "clumsy.h"

int main(){
    int fd;
    char ch, write_buf[100], read_buf[11];
    int a = 0;

    fd = open("/dev/clumsy0", O_RDWR);

    while (1){
        printf("\nRead from device (R)\nWrite to device (W)\n");
        scanf(" %c", &ch);

        if(ch == 'r'){
            memset(read_buf, 0, sizeof(read_buf));
            printf("\nRandom drop read (r)\nRegular drop read (n)\n");
            scanf(" %c", &ch);
            if (ch == 'r'){
                ioctl(fd, CLUMSY_SET_RANDOM_MODE, 0);
                read(fd, read_buf, sizeof(read_buf)-sizeof(char));
                printf("device: %s\n", read_buf);
            }else{
                int index;
                printf("enter index:");
                scanf("%d", &index);
                ioctl(fd, CLUMSY_SET_REGULAR_MODE, index);
                read(fd, read_buf, sizeof(read_buf)-sizeof(char));
                printf("device: %s\n", read_buf);
            }
        } else if(ch == 'w') {
        memset(write_buf, 0, sizeof(write_buf));
            printf("Enter the string: ");
            scanf(" %s", write_buf);
            printf("\n%d", strlen(write_buf));
            write(fd, write_buf, (strlen(write_buf))*sizeof(char));

        } else if(ch == 'e') {
            printf("Cikiliyor ...\n");
            break;
        }

    }

    close(fd);

    return 0;

}
