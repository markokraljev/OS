#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int id = fork(); //2^n vo zavisnost od toa kolku pati prakjame fork
    if(id != 0){
        fork();
        printf("Jas sum vo main process!\n");
    }
    printf("Hello world\n");
   // if (id==0){
   //     printf("Hello from chlid process\n");
   // }
   // else{
    //    printf("Hello from the main process\n");
    //}
    return 0;
}

//Ako sakame da imame 3 procesi togas kako?
//Treba da ima if koj proveruva dali nasiot id e 0 i ako e togas ne povikuva fork pak
//Sto znaci deka ako sme vo main procesot togas povikuvame fork

//Dete funkcija sekogas kje bide 0 a pid na roditel e sekogas razlicen od dete proces dete proces kje ima pid 0
//Za da znaes dali si vo main process ili child process se gleda spored pid