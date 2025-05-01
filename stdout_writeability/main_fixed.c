#include <stdio.h>
#include <errno.h> // For errno

int main() {
    int result = printf("Hello CLang\n");
    if (result < 0) {
        fprintf(stderr, "Error writing to stdout. Error code: %d\n", errno);
        return 1;
    }
    return 0;
}
