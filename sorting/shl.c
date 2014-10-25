/* shell sort */

#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

void shellSort(int *a, int lb, int ub) {
    int i, j;
    unsigned int n;
    int t;

    static const unsigned int h[] = {
        1, 5, 19, 41, 109, 209, 505, 929, 2161, 3905, 8929, 
        16001, 36289, 64769, 146305, 260609, 587521, 1045505,
        2354689, 4188161, 9427969, 16764929, 37730305, 67084289, 
        150958081, 268386305, 603906049, 1073643521, 2415771649U
    };

    /* find t such that 3*h[t] >= n */
    n = ub - lb + 1;
    for (t = 0; 3*h[t] < n; t++);

    /* start with h[t-1] */
    if (t > 0) t--;

    while (t >= 0) {
        unsigned int ht;

        /* sort-by-insertion in increments of h */
    	ht = h[t--];
        for (i = lb + ht; i <= ub; i++) {
            int tmp = a[i];
            for (j = i-ht; j >= lb && compGT(a[j], tmp); j -= ht)
                a[j+ht] = a[j];
            a[j+ht] = tmp;
        }
    }
}

int mainShl(int *a, int lb,int ub) {
    shellSort(a, lb, ub);
    return 0;
}
