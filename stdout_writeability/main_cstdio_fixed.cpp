#include <cstdio>
#include <cerrno> // For errno

int main() {

    fflush(stdout);
    int result = fprintf(stdout, "Hello cstdio!\n");
    if (result < 0) {
        if (errno == ENOSPC) {
            perror("Error writing to stdout: No space left on the device");
        } else {
            perror("Error writing to stdout");
        }
        return 1;
    }

    return 0;
}
