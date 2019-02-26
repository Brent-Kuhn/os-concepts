#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"

void print_all_pstat_info();
void print_pstat_info(int pid);

int main(int argc, char *argv[])
{
    settickets(20);
    printf(1, "pstat_info before children: \n");
    print_all_pstat_info();
    printf(1, "creating children and printing pstat info...\n");
    int i = 0, pid = 0;
    for (i = 1; i <= 10; i++) {
        pid = fork();
        if (pid == 0) {
            settickets(i*10);
            print_pstat_info(getpid());
            exit();
        } else {
            wait();
        }
    } 
    exit();
    return 0;
}

void print_all_pstat_info() {
    struct pstat data;
    getpinfo(&data);
    int i = 0;
    for(i = 0; i < 64; i++) {
        if(data.inuse[i] == 0) {
            continue;
        }
        printf(1, "Process id: %d has %d tickets and %d pass value\n", data.pid[i], data.tickets[i], data.ticks[i]);
    }
}

void print_pstat_info(int pid) {
    struct pstat data;
    getpinfo(&data);
    int i = 0;
    for(i = 0; i < 64; i++) {
        if(data.inuse[i] == 0 || data.pid[i] != pid) {
            continue;
        }
        printf(1, "Process id: %d has %d tickets and %d pass value\n", data.pid[i], data.tickets[i], data.ticks[i]);
    }
}

