/* quicksort, for linked lists */

#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

typedef struct listTag {        /* typical node to be sorted */
    struct listTag *next;
    struct listTag *prev;
    int data;
} listNode;
 
listNode *partitionQuiList(listNode *lb, listNode *rb) {
    int t, pivot;
    listNode *i, *j;
    int done;           /* record if pointers cross (means we're done!) */

   /********************************************************
    * partition list [lb..rb], and return pointer to pivot *
    ********************************************************/

    /* select a pivot */
    pivot = lb->data;
    done = 0;

    /* scan from both ends, swapping when needed */
    /* care must be taken not to address outside [lb..rb] with pointers */
    i = lb; j = rb;
    while(1) {
        while (compGT(j->data, pivot)) {
            j = j->prev;
            if (i == j) done = 1;
        }
        if (done) return j;
        while (compLT(i->data, pivot)) {
            i = i->next;
            if (i == j) done = 1;
        }
        if (done) return j;

        /* swap i, j */
        t = i->data;
        i->data = j->data;
        j->data = t;

        /* examine next element */
        j = j->prev;
        if (i == j) done = 1;
        i = i->next;
        if (i == j) done = 1;
    }
}

void quickSortQuiList(listNode *lb, listNode *rb) {
    listNode *m;

   /************************
    *  sort list [lb..rb]  *
    ************************/

    if (lb == rb) return;

    m = partitionQuiList(lb, rb);

    if (m != lb) quickSortQuiList(lb, m);              /* sort left side */
    if (m != rb) quickSortQuiList(m->next, rb);        /* sort right side */
}

int mainQuiList(int *a, int lb,int ub) {
    /* command-line:
     *
     *   quilist maxnum
     *
     *   quilist 2000
     *       sorts 2000 records
     *
     */

    listNode *p0;
    int maxnum=ub-lb, i;

    if ((p0 = malloc(maxnum * sizeof(listNode))) == 0) {
        fprintf (stderr, "insufficient memory (a)\n");
        exit(1);
    }

    /* initialize list */
    for (i = 0; i < maxnum; i++) {
        p0[i].next = p0 + i + 1;
        p0[i].prev = p0 + i - 1;
        p0[i].data = a[i];
    }

    quickSortQuiList(p0, p0 + maxnum-1);

    return 0;
}
