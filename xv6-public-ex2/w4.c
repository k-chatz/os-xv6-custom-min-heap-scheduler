#include "types.h"
#include "stat.h"
#include "user.h"

char buf;

void w2(int fd) {
    int n;

    while ((n = read(fd, &buf, sizeof(buf))) > 0) {
        int i, j, x = 0, res = 0;
        for (i = 0; i < 999; ++i) {
            for (j = 0; j < 99999; ++j) {
                ++x;
                x += j % 2;
                res += (x + 1 * j * x ) + buf;
            }
        }
        //printf(1, "res = %d\n", res);
    }

    if (n < 0) {
        printf(1, "w4: read error\n");
        exit();
    }
}

int main(int argc, char *argv[]) {
    printf(1, "w4(%d) is running now\n", getpid());

    int fd, i;

    if (argc <= 1) {
        w2(0);
        exit();
    }

    for (i = 0; i < 50; i++) {
        if ((fd = open(argv[1], 0)) < 0) {
            printf(1, "w4: cannot open %s\n", argv[i]);
            exit();
        }
        w2(fd);
        close(fd);
    }

    exit();
}

