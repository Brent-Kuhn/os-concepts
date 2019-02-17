#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"

int
main(int argc, char *argv[])
{
    struct pstat data;
    getpinfo(&data);
    int i = 0;
    for(i = 0; i < 64; i++) {
        if(data.inuse[i] == 0) {
            continue;
        }
        printf(1, "Process id: %d has %d tickets and %d pass value\n", data.pid[i], data.tickets[i], data.ticks[i]);
    }
    exit();
    return 0;
}
