#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
//povikuvanje na povekje fork procesi

int main(int argc,char* argv[]){
    int id1=fork();
    int id2=fork(); //4 procesi ama kako izgleda hierarhijata na tie procesi?
    if (id1==0){
        if(id2==0){
            printf("We are process y\n");
        }
        else{
            printf("We are process x\n");
        }
    }
    else{
        if(id2==0){
            printf("We are process z\n");
        }
        else{
            printf("We are the parent process!\n");
        }
    }
    //wait(NULL); //ova ne znaci cekaj gi SITE dete procesi. Procesi mozat da se terminiraat!!
    while (wait(NULL)!=-1 || errno!=ECHILD){ //errno e error number i toa obicno za nekoja globalna sistemska funkcija vrakja vrednost za greska
        printf("Waited for a child to finish\n");
    }    
    return 0;
    //errno vrakja obicno -1 ili NULL i taa postavuva broj tocno vo errno za da znaeme kaj nastanala greskata
    //ECHILD znaci deka imame No Child Process ni dava broj za greska na child process
    //Za da se vidi errno greska se koristi perror("Poraka") ili sterror(errno) od string.h
}

//Procesite odat vaka
//Parent ||
//       \/
//Proces X i Proces Z ||
//                    \/
//                 Proces Y