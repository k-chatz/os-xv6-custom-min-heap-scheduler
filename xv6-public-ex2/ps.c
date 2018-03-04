#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(void)
{
    for (;;) {
        printRunningProc();
        sleep(100);
    }

    exit();
}
