/* qsort() */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXSTACK (sizeof(size_t) * CHAR_BIT)

#define exchange(a, b, size) \
{ \
    size_t s; \
    int *ai, *bi; \
    char *ac, *bc; \
    ai = (int *)a; \
    bi = (int *)b; \
    for (s = sizeof(int); s <= size; s += sizeof(int)) { \
        int t = *ai; \
        *ai++ = *bi; \
        *bi++ = t; \
    } \
    ac = (char *)ai; \
    bc = (char *)bi; \
    for (s = s - sizeof(int) + 1; s <= size; s++) { \
        char t = *ac; \
        *ac++ = *bc; \
        *bc++ = t; \
    } \
}

void qsort(void *base, size_t nmemb, size_t size,
        int (*compar)(const void *, const void *)) {
    void *lbStack[MAXSTACK], *ubStack[MAXSTACK];
    int sp;
    unsigned int offset;

    /********************
     *  ANSI-C qsort()  *
     ********************/

    lbStack[0] = (char *)base;
    ubStack[0] = (char *)base + (nmemb-1)*size;
    for (sp = 0; sp >= 0; sp--) {
        char *lb, *ub, *m;
        char *P, *i, *j;

        lb = (char *)lbStack[sp];
        ub = (char *)ubStack[sp];

        while (lb < ub) {

            /* select pivot and exchange with 1st element */
            offset = (ub - lb) >> 1;
            P = lb + offset - offset % size;
            exchange (lb, P, size);

            /* partition into two segments */
            i = lb + size;
            j = ub;
            while (1) {
                while (i < j && compar(lb, i) > 0) i += size;
                while (j >= i && compar(j, lb) > 0) j -= size;
                if (i >= j) break;
                exchange (i, j, size);
                j -= size;
                i += size;
            }

            /* pivot belongs in A[j] */
            exchange (lb, j, size);
            m = j;

            /* keep processing smallest segment, and stack largest */
            if (m - lb <= ub - m) {
                if (m + size < ub) {
                    lbStack[sp] = m + size;
                    ubStack[sp++] = ub;
                }
                ub = m - size;
            } else {
                if (m - size > lb) {
                    lbStack[sp] = lb; 
                    ubStack[sp++] = m - size;
                }
                lb = m + size;
            }
        }
    }
}
//
//void fillQSort(int *lb, int *ub) {
//    int *i;
//    srand(1);
//    for (i = lb; i <= ub; i++) *i = rand();
//}

int Comp(const void *a, const void *b) { return *(int *)a - *(int *)b; }

int mainQSort(int *a, int lbIn,int ubIn) {
	int maxnum = ubIn-lbIn;
    int  *lb, *ub;
	 
    lb = a;  ub = a + maxnum - 1;
    qsort(a, maxnum, sizeof(int), Comp);
    return 0;
}
