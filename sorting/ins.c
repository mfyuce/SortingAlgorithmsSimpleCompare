/* insert sort */

#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"
 

void insertSort(int *a, int lb, int ub) {
	int t;
	int i, j;

	/**************************
	*  sort array a[lb..ub]  *
	**************************/
	for (i = lb + 1; i <= ub; i++) {
		t = a[i];

		/* Shift elements down until */
		/* insertion point found.    */
		for (j = i-1; j >= lb && compGT(a[j], t); j--)
			a[j+1] = a[j];

		/* insert */
		a[j+1] = t;
	}
} 

int mainIns(int *a, int lb,int ub) {
	insertSort(a, lb, ub);
	return 0;
}
