#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        /* Child process: replace image with a new program */
        char *args[] = {"sleep", "30", NULL};
        execvp(args[0], args);
        perror("execvp");
        return EXIT_FAILURE;
    }

    /* Parent process: wait for child and print its exit status */
    int status;
    if (waitpid(pid, &status, 0) < 0) {
        perror("waitpid");
        return EXIT_FAILURE;
    }

    if (WIFEXITED(status)) {
        printf("Child exited with status %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("Child terminated by signal %d\n", WTERMSIG(status));
    } else {
        printf("Child ended with unknown status 0x%x\n", status);
    }

    return EXIT_SUCCESS;
}
