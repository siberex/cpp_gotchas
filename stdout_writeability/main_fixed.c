#include <stdio.h>
#include <errno.h> // For errno

int main() {
    printf("Hello CLang\n");
    if (fflush(stdout) == EOF) {
        fprintf(stderr, "Error writing to stdout. Error code: %d\n", errno);
        perror("");
        return 1;
    }
    return 0;
}