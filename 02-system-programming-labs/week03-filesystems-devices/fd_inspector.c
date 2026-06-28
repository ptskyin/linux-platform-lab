#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    const char *filename = "fd_inspector_sample.txt";
    int fd;

    if (argc > 1) {
        filename = argv[1];
    }

    fd = open(filename, O_CREAT | O_RDWR, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    printf("Opened file: %s\n", filename);
    printf("Process ID: %d\n", getpid());
    printf("File descriptor: %d\n", fd);
    printf("Inspect while sleeping: ls -l /proc/%d/fd\n", getpid());
    printf("Sleeping for 30 seconds...\n");
    fflush(stdout);

    sleep(30);

    close(fd);
    printf("Closed file descriptor %d\n", fd);

    return 0;
}
