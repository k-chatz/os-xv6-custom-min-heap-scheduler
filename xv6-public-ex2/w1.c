#include "types.h"
#include "stat.h"
#include "user.h"

/*http://www.techcrashcourse.com/2015/11/c-program-to-print-all-prime-numbers-between-1-to-N.html*/
int main(void) {
    //printf(1, "w1(%d) is running now\n", getpid());
    int i, j, x = 0, res = 0;
    for (i = 0; i < 99999; ++i) {
        for (j = 0; j < 99999; ++j) {
            x = j % 2;
            res += (i +1* j * x);
        }
    }
    printf(1, "res = %d\n", res);
    exit();
}
