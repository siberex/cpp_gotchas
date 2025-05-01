#include <cstdio>
#include <cerrno> // For errno

int main() {
    fprintf(stdout, "Hello cstdio!\n");
    if (fflush(stdout) == EOF) {
        if (errno == ENOSPC) {
            fprintf(stderr, "Error writing to stdout: No space left on device (os error %d)\n", errno);
        } else {
            perror("Error writing to stdout");
        }
        return 1;
    }

    return 0;
}
