//Proba so gemini da se naucam Shared Memorija

//Mal run-down sto treba da se znae
/* Glavniot tek na rabota sodrzi 4 cekori
 - Ja koristi shm_open() funkcijata koja kreira ili otvara spodelen memoriski object
 - Ja koristi ftructate() funkcijata koja ja definira goleminata na memorijata vo bajti
 - Ja koristi mmap() funkcijata koja go mapira objektot vo adresniot prostor na procesot i vrakja pointer
 - Ja koristi munmap() / shm_unlink() za da go oslobodi pokazuvacot i go brise memoriskiot objekt vo sistemot*/

 //Primer kod:

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <fcntl.h>
 #include <sys/mman.h>
 #include <sys/stat.h>
 #include <sys/wait.h>
 #include <unistd.h>

 #define SHM_MARKO "/my_shared_mem"
 #define MEM_SIZE 4096

 //Definirame struktura
 typedef struct{
    int id;
 } SharedMem;

 int main(int argc,char *argv[]){
    int shm_fd=shm_open(SHM_MARKO, O_CREAT | O_RDWR, 0666); //inicijalizacija na sharedmem
    //Memorija kade treba da se koristi so define
    // da se kreira za read i write 
    // ako prv pat ja kreiras memorijata mora da gi imas dodeleno slednite flagovi za permisija 0666
    
    if(shm_fd == -1 ){ //If uslov za greska da proverime
        printf("Error shm_open()");
        return 1;
    }
    
    //Postavuvame golemina na memorijata sto ja delime
    ftruncate(shm_fd, sizeof(SharedMem));

    //Mapiranje (Kastiranje vo nasiot tip na podatok)
    SharedMem *data=(SharedMem *)mmap(0, sizeof(SharedMem), PROT_READ | PROT_WRITE , MAP_SHARED, shm_fd, 0);
    //kaj mmap 0 -addr mu kazuvame kade da smesti vo virtuelna memorija nekakov blok najcesto NULL ili 0
    //sizeof - golemina normalno, prot e protection mu kazuva na os dali da cita ili zapisuva nie sme stavile i toa i toa
    //MAP_SHARED e flag koj znaci deka site promeni vo memorijata kje bidat vidlivi za drugi procesi shm_fd e deskriptor
    // 0 e offset
    
    if(data==MAP_FAILED){ //proverka za greska pri mmap
        perror("Greska pri mmap");
        return 2;
    }
    
    int id = fork();
    if (id==-1){
        printf("Greska so fork process");
        return 3;
    }

    if (id==0){
        //dete proces
        printf("Jas sum dete i zapisuvam podatoci vo shared memory\n");
        data->id=101;
        munmap(data,sizeof(SharedMem));
        exit(0);
    }
    else{
        //roditel proces
        wait(NULL); //cekame deteto da zavrsi
        printf("Jas sum roditelot i cekam deteto da zavrsi pred da citam\n");
        printf("-> ID: %d\n",data->id);
        munmap(data,sizeof(SharedMem));
        shm_unlink(SHM_MARKO);
    }
    return 0;
}