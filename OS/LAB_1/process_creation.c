#include <stdio.h>
#include <unistd.h>

int main() {
    int pid;
    pid = fork(); /* fork another process */

    if (pid < 0) {
        /* error occurred */
        printf("Child process creation failed\n");
    }
    else if (pid == 0) {
        /* child process */
        printf("This is the child process. PID: %d\n", getpid());
    }
    else {
        /* parent process */
        printf("This is the parent process. Child PID: %d\n", pid);
    }

    return 0;
}
