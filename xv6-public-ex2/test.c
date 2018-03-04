#include "types.h"
#include "stat.h"
#include "user.h"


int main(void)
{

    printf(1, "\nUnix V6 was released in the year %d\n", getyear());

    printf(1, "\nThe total number of system calls so far is %d\n", numcalls());

    printf(1, "\nUp time %d\n", uptime());

    printf(1, "\nRemove running processes from scheduler...\n");

    drop_ready_processes();

    exit();
}