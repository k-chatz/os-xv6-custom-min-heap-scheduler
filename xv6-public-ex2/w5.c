#include "types.h"
#include "stat.h"
#include "user.h"

char buf[10000];

void w3(int fd) {
    int n;

    while ((n = read(fd, &buf, sizeof(buf))) > 0) {
        int i, j, x = 0, res = 0;
        for (i = 0; i < 999; ++i) {
            for (j = 0; j < 99999; ++j) {
                ++x;
                x += j % 2;
                res += (x + 1 * j * x ) + buf[i];
            }
        }
        //printf(1, "res = %d\n", res);
    }


    if (n < 0) {
        printf(1, "w5: read error\n");
        exit();
    }
}

int main(int argc, char *argv[]) {
    printf(1, "w5(%d) is running now\n", getpid());

    int fd, i;

    if (argc <= 1) {
        w3(0);
        exit();
    }

    for (i = 0; i < 10000; i++) {
        if ((fd = open(argv[1], 0)) < 0) {
            printf(1, "w5: cannot open %s\n", argv[i]);
            exit();
        }
        w3(fd);
        close(fd);
    }

    exit();
}
