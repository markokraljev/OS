#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    int id=fork();
    if(id==0){
        sleep(1);
    } //Ako umre parent procesot dete procesot dobiva nov ppid i se vika deka e zombie proces bidejkji so 
    //sigkill nema da se ubie procesot i kje dobieme memory leak
    printf("Current id %d, parent id:%d \n", getpid(),getppid());
    //wait(NULL); //Ne mora da se proveri dali e parent za da se povika wait
    //Koga se povikuva wait sekogas se razbira za da se ceka dete procesot

    int res=wait(NULL);
    if(res==-1){
        printf("Nema deca za cekanje\n");
    }
    else{
        printf("%d zavrsiv so izvrsuvanje\n",res);
    }
    
    return 0;
}