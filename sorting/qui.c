/* quicksort */

#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"


void sortByInsertion(int *x, int lb, int ub) {
    int i, j;

    for (i = lb + 1; i <= ub; i++) {
        int t = x[i];

        /* shift down until insertion point found */
        for (j = i-1; j >= 0 && compGT(x[j], t); j--)
            x[j+1] = x[j];

        /* insert */
        x[j+1] = t;
    }
}

int partition(int *x, int lb, int ub) {

    /* select a pivot */
    double pivot = x[(lb+ub)/2];

    /* work from both ends, swapping to keep   */
    /* values less than pivot to the left, and */
    /* values greater than pivot to the right  */
    int i = lb - 1;
    int j = ub + 1;
    while (1) {
        int t;

        while (compGT(x[--j], pivot));
        while (compLT(x[++i], pivot));
        if (i >= j) break;

        /* swap x[i], x[t] */
        t = x[i];
        x[i] = x[j];
        x[j] = t;
    }

    return j;
}

void quickSort(int *x, int lb, int ub) {
    int m;

    if (lb >= ub) return;
    m = partition(x, lb, ub);
    quickSort(x, lb, m);
    quickSort(x, m + 1, ub);
}

void quickSortImproved(int *x, int lb, int ub) {
    while (lb < ub) {
        int m;

        /* quickly sort short lists */
        if (ub - lb <= 50) {
            sortByInsertion(x, lb, ub);
            return;
        }

        m = partition(x, lb, ub);

        /* eliminate tail recursion and */
        /* sort the smallest partition first */
        /* to minimize stack requirements    */
        if (m - lb <= ub - m) {
            quickSortImproved(x, lb, m);
            lb = m + 1;
        } else {
            quickSortImproved(x, m + 1, ub);
            ub = m;
        }
    }
}
 
int mainQui(int *a, int lb,int ub) {
    quickSortImproved(a, lb, ub);
    return 0;
}
