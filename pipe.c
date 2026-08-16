#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc,char* argv[]){
    int fd[2];//fd-file descriptor fd[0]-read fd[1]-write
    if(pipe(fd)==-1){
        printf("An error occured with opening the pipe");//zima array od 2 integeri
        return 1;
    }
    int id=fork(); //fd se kopira se inheritnuva odnosno nezavisni se 
    if(id==-1){
        printf("An error occured with fork!\n");
        return 4; //se dodava error message za sekoja funkcija bidejkji taka znaeme ako sme imale nekakvi greski vo kodot
    }
    if (id==0){
        close(fd[0]); //Standard se zatvara edna strana
        int x;
        printf("Input a number: ");
        scanf("%d",&x);
       if( write(fd[1], &x, sizeof(int))==-1);{
        printf("An error occured with writing to the pipe\n");
        return 2;
    } //vikame deka sakame da zapisuvame (write e univerzalna funkcija i raboti za sekoj file)
        close(fd[1]);// stom zatvarame write zatvarame citanje
        // sakame da ja zapiseme adresata na x i goleminata na integerot sto go vnesuvame i koga zavrsuvame so zapisuvanje go gasime file descriptorot 
    } else{
        close(fd[1]);//zatvarame zapisuvanje posto vo ovoj proces ne zapisuvame tuku citame od dete procesot
        int y;
        if(read(fd[0], &y, sizeof(int))==-1){
            printf("An error occured with reading from the pipe\n");
            return 3;
        }
        y=y*3;
        close(fd[0]);
        printf("Got from child process: %d\n",y); //pecati sto ti kaza deteto
    } 
    return 0;
}
//Pipe e in-memory file koj ima buffer koj e zacuvan vo memorija i tamu mozeme da pisuvame i zapisuvame
