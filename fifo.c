#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc,char* argv[]){
    if(mkfifo("myfifo1", 0777)==-1){
        if(errno!=EEXIST){
            printf("Could not create fifo file\n");
            return 1;
        }
    }//0777 mu kazuva na operativniot sistem deka myfifo1 file-ot kje bide dostapen za citanje/zapisuvanje od sekoj
    printf("Opening...\n");
    int fd = open("myfifo1", O_WRONLY); //go otvarame fifoto za zapisuvanje ONLY
    if(fd==-1){
        printf("error za otvaranje na myfifo1");
        return 3;
    }
    int x=97; //O_RDWR read and write i nema da se terminira  bidejkji otvoreno e za dvete i za read i write
    printf("Opened\n");
    if(write(fd, &x,sizeof(x))==-1){
        printf("Error while writing");
        return 2;
    } //za komunikacija moras da otvoris drug terminal i so cat myfifo1 da ranuvas za da moze da dovrsi so rabota fifoto
    printf("Writing"); //koga zapisuva ednata strana mora da se otvori za citanje
    close(fd); //99% od vremeto za zapisuvanje vaka se koristi
    printf("Closed");
    return 0;// se kreira myfifo1 dokument
}