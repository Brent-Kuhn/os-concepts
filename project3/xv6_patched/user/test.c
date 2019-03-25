// Test program for NULL pointer
#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
    int ppid = getpid();

    int pid =fork();
    if (pid < 0) {
        printf(1, "Test failed\n");
        exit();
    } else if (pid == 0) {
        uint * nullp = (uint*)0;
        printf(1, "null dereference: ");
        printf(1, "%x %x\n", nullp, *nullp);
        // this process should be killed
        printf(1, "Test failed\n");
        kill(ppid);
        exit();
    } else {
        wait();
        printf(1, "Test Passed\n");
        exit();
    }
};

// int nullTest2(int argc, char *argv[]) {
//     char *arg;

//     int fd = open("tmp", 0_WRONLY|0_CREATE);
//     assert(fd != -1);

//     // at zero
//     arg = (char*) 0x0;
//     assert(write(fd, arg, 10) == -1);

//     // within null page
//     arg = (char*) 0x400;
//     assert(write(fd, arg, 1024) == -1);

//     // spanning null page and code
//     arg = (char*) 0xfff;
//     assert(write(fd, arg, 2) == -1);

//     printf(1, "TEST PASSED\n");
//     exit();
// };