#include <errno.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static const char handler_msg[] = "Caught SIGINT, exiting cleanly...\n";
static const char ok_msg[] = "Signal handler registered. Press Ctrl+C to quit.\n";

static void sigint_handler(int signo)
{
    (void)signo;
    ssize_t ignored = write(STDOUT_FILENO, handler_msg, sizeof(handler_msg) - 1);
    (void)ignored;
    _exit(EXIT_SUCCESS);
}

int main(void)
{
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = sigint_handler;
    sa.sa_flags = SA_RESTART;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        fprintf(stderr, "sigaction(SIGINT) failed: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    if (write(STDOUT_FILENO, ok_msg, sizeof(ok_msg) - 1) == -1) {
        fprintf(stderr, "write() failed: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    for (;;) {
        pause();
    }

    return EXIT_SUCCESS;
}
