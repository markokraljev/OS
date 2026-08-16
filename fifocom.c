#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc,char* argv[]){
    int arr[5];
    srand(time(NULL));
    int i=0;
    for(i=0;i<5;i++){
        arr[i]=rand()%100;
    }
    int fd=open("sum",O_WRONLY);
    if(fd==-1){
        printf("Error");
        return 1;
    }
    //Go kreiravme sum od terminal so mkfifo sum
    for(i=0;i<5;i++){
        if(write(fd,&arr[i],sizeof(int))==-1){
            return 2;
        }
        printf("Wrote %d\n",arr[i]);
    }
    return 0;
}