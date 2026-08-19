#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void run_child(void (*func)()) {
    pid_t pid = fork();
    if (pid == 0) {
        func(); // Синот ја повикува соодветната exec функција
        perror("Exec не успеа");
        exit(1);
    }
    wait(NULL); // Таткото чека да заврши синот пред да прејде на следниот пример
    printf("----------------------------------------\n");
}

// 1. execl - List, Цела патека
void demo_execl() {
    printf("1. Running execl:\n");
    execl("/bin/ls", "ls", "-l", NULL);
}

// 2. execlp - List, Користи PATH (не мора цела патека)
void demo_execlp() {
    printf("2. Running execlp:\n");
    execlp("ls", "ls", "-l", NULL);
}

// 3. execv - Vector (низа), Цела патека
void demo_execv() {
    printf("3. Running execv:\n");
    char *args[] = {"ls", "-l", NULL};
    execv("/bin/ls", args);
}

// 4. execvp - Vector (низа), Користи PATH (НАЈЧЕСТО СЕ КОРИСТИ)
void demo_execvp() {
    printf("4. Running execvp:\n");
    char *args[] = {"ls", "-l", NULL};
    execvp("ls", args);
}

// 5. execve - Vector (низа), Цела патека + Environment променливи
void demo_execve() {
    printf("5. Running execve:\n");
    char *args[] = {"env", NULL}; // Команда за печатење на environment
    char *env[] = {"USER_MODE=ExamPrep", "TEST_VAR=123", NULL};
    
    // Прикажува само променливи што ние експлицитно ги пративме во env
    execve("/usr/bin/env", args, env); 
}

int main() {
    run_child(demo_execl);
    run_child(demo_execlp);
    run_child(demo_execv);
    run_child(demo_execvp);
    run_child(demo_execve);

    return 0;
}
