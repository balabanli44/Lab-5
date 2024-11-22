
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void child1() {
    int num1, num2;
    printf("Child 1: Enter two numbers: ");
    scanf("%d %d", &num1, &num2);
    printf("Child 1: The sum is %d\n", num1 + num2);
    exit(0); // Exit the process
}

void child2() {
    char name[50];
    printf("Child 2: Enter your name: ");
    scanf("%s", name);
    printf("Child 2: Hello, %s!\n", name);
    exit(0); // Exit the process
}

int main() {
    pid_t pid1, pid2, finished;

    pid1 = fork(); // Create the first child process
    if (pid1 == 0) {
        child1();
    }

    pid2 = fork(); // Create the second child process
    if (pid2 == 0) {
        child2();
    }

    // Parent process: Wait for children to complete
    int status;
    for (int i = 0; i < 2; i++) {
        finished = wait(&status); // Wait for any child to complete
        if (finished == pid1) {
            printf("Parent: Child 1 finished\n");
        } else if (finished == pid2) {
            printf("Parent: Child 2 finished\n");
        }
    }

    printf("Parent: All children completed.\n");
    return 0;
}
