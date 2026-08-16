//test.c bese cisto za da vidam kako se korsiti fork funkcijata ova e za kako vo procesi se koristi wait!
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[]){
    int id=fork();
    int n;
    if (id==0){
        n=1;
    }
    else{
        n=6;
    }
    if (id!=0){ //ako ne si dete proces vlezi vo if uslovot i cekaj go dete procesot
        wait(); //cekaj go dete procesot pa pocni da rabotis
    }
    int i;
    for(i=n;i<n+5;i++){ //bez wait dvata procesi od ednas se ranuvaat i se mesaat
        printf("%d ",i);
        fflush(stdout);
    }
    //mi javuva greska ama ne mislam deka e nesto problem toa sto e na pocetokot
    return 0;
}