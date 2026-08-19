//Reshenie na 3ta labs
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <fcntl.h>
 #include <sys/mman.h>
 #include <sys/stat.h>
 #include <sys/wait.h>
 #include <unistd.h>
 #include <string.h>
 #include <time.h>

 #define SHM_MARKO "/my_shared_mem"
 #define MEM_SIZE 4096

 //Definirame struktura
 typedef struct {
    int bajt;
    char zborce[50];
 } Shared;

 int main(int argc,char *argv[]){
    int shm_fd=shm_open(SHM_MARKO, O_CREAT | O_RDWR, 0666); //inicijalizacija na sharedmem
    
    if(shm_fd == -1 ){ //If uslov za greska da proverime
        printf("Error shm_open()");
        return 1;
    }
    
    //Postavuvame golemina na memorijata sto ja delime
    ftruncate(shm_fd, sizeof(Shared));

    //Mapiranje (Kastiranje vo nasiot tip na podatok)
    Shared *data=(Shared *)mmap(0, sizeof(Shared), PROT_READ | PROT_WRITE , MAP_SHARED, shm_fd, 0);
    
    if(data==MAP_FAILED){ //proverka za greska pri mmap
        perror("Greska pri mmap");
        return 2;
    }
    
    int id1 = fork();
    int id2 = fork();
    if( id2 == -1 ){
        printf("Greska so fork process 2");
        return 4;
    }
    if (id1 == -1){
        printf("Greska so fork process 1");
        return 3;
    }

    if (id1 == 0){
        //dete proces prv proces
        printf("Vnesete zbor:");
        fgets(data->zborce,sizeof(data->zborce),stdin);
        data->zborce[strcspn(data->zborce,"\n")]=0;
        data->bajt=1;
        if(data->bajt==1 && data->zborce!=NULL){
            printf("Zapisan e zbor vo memorija!");
        }
        int timesleep=rand()%10+1;
        printf("Jas sega kje spijam %d",timesleep);
    }
    else{
        //roditel proces
        wait(NULL); //cekame deteto da zavrsi
        printf("Zborot sto sakam da go procitam sto e vnesen e: %s\n",data->zborce);
    }
    if( id2 == 0 ){
        //dete proces na vtoriot fork

    }
    munmap(data,sizeof(Shared));
    shm_unlink(SHM_MARKO);
    munmap(data,sizeof(Shared));
    return 0;
}