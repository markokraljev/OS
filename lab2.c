#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int N;
    printf("Vnesi kolku pati da se izvrshi naredbata (N): ");
    if (scanf("%d", &N) != 1 || N <= 0) {
        printf("Nevaliden broj N.\n");
        return 1;
    }

    int nacin = atoi(argv[1]); // 0 za paralelno, 1 za sekvencijalno
    //atoi sluzi za da moze nekoj string kako 0 ili 1 vo ovoj slucaj da se predade kako integer

    if (nacin == 1) {
        // SEKVENCIJALNO: Roditelot mora da ceka vnatre vo ciklusot
        for (int i = 0; i < N; i++) {
            pid_t id = fork();
            if (id < 0) {
                printf("Error so fork\n");
                return 1;
            }
            if (id == 0) {
                // Deteto ja izvrshuva naredbata (pochnuva od argv[2])
                if (execvp(argv[2], &argv[2]) == -1 ){
                  printf("Greska so execvp\n");
                  return 2;
                }
            } else {
                // Roditelot ceka sekoe dete POEDINECNO pred da napravi novo
                wait(NULL);
            }
        }
    } 
    else if (nacin == 0) {
        // PARALELNO: Roditelot gi kreira site N deca odednash
        for (int i = 0; i < N; i++) {
            pid_t id = fork();
            if (id == -1) {
                printf("Fork error\n");
                return 3;
            }
            if (id == 0) {
                if ( execvp(argv[2], &argv[2]) == -1 ){
                    printf("Execvp error\n");
                    return 4;
                }
            }
        }
        
        // Otkako ги napravi site, sega gi ceka site N deca da zavrsat
        for (int i = 0; i < N; i++) {
            wait(NULL);
        }
    } 
    else {
        printf("Prviot argument mora da bide 0 ili 1.\n");
        return 5;
    }

    // 3. Pechatenje na porakata koga KJE ZAVRSHAT SITE
    printf("Zavrshuva process 0\n");

    return 0;
}
