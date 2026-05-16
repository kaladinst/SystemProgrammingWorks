#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

void handle_sigint(int sig) {
    printf("Child: SIGINT received but continuing...\n");
    fflush(stdout);
}

void handle_sigcont(int sig) {
    printf("Child: Process resumed\n");
    fflush(stdout);
}

void handle_alarm(int sig) {
}

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        signal(SIGINT, handle_sigint);
        signal(SIGCONT, handle_sigcont);

        int counter = 0;
        while (1) {
            printf("Child counter: %d\n", counter);
            fflush(stdout);
            counter++;
            sleep(1);
        }
    } else {
        signal(SIGALRM, handle_alarm);

        for (int i = 0; i < 1; i++) {
            alarm(3);
            pause();

            printf("Parent: Stopping child...\n");
            fflush(stdout);
            kill(pid, SIGSTOP);

            sleep(2);

            printf("Parent: Continuing child...\n");
            fflush(stdout);
            kill(pid, SIGCONT);
        }

        printf("Parent: Sending SIGINT...\n");
        fflush(stdout);
        kill(pid, SIGINT);

        sleep(1);
        kill(pid, SIGKILL);
        wait(NULL);

        printf("Parent: Child terminated.\n");
        fflush(stdout);
    }

    return 0;
}