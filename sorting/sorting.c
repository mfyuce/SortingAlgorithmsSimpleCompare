#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sorting.h"

void fill(int *a, int lb, int ub) {
	int i;
	srand(1);
	for (i = lb; i <= ub; i++) a[i] = rand();
}
void export(int *a, int lb, int ub) {
	FILE   *ofp;
	int i; 
	char * outputFilename = "out.list";
	ofp = fopen(outputFilename, "w");

	if (ofp == NULL) {
		fprintf(stderr, "Can't open output file %s!\n",
			outputFilename);
	}
	for (i = lb; i <= ub; i++){
		fprintf(ofp, "%d\n", a[i]);
	}
	fclose(ofp);
}

void import(char * file,int* a, int lb, int ub) {
	FILE   *ifp;
	int i,tmp,maxnum; 
	;
	ifp = fopen(file, "r");
	if (ifp == NULL) {
		fprintf(stderr, "Can't open output file %s!\n",
			file);
	}
	maxnum = ub-lb;
	i=0;
	while (fscanf(ifp, "%d", &tmp) != EOF) { 
		a[i++]=tmp;
	} 
	fclose(ifp);
}
int main(int argc, char *argv[]) {
	int maxnum, lb, ub, i;
	int *a;
	clock_t start  , diff;
	int msec;
	/* command-line:
	*
	*   ins maxnum importFile
	*
	*   ins 2000 average.list
	*       sorts 2000 records
	*
	*/

	maxnum = atoi(argv[1]);
	lb = 0; ub = maxnum - 1;
	if ((a = malloc(maxnum * sizeof(int))) == 0) {
		fprintf (stderr, "insufficient memory (a)\n");
		exit(1);
	}
	if(argc>2){
		import(argv[2],a,lb,ub);
	}else{
		fill(a,lb,ub);
	}
	/*Export*/
	//export( a,   lb,   ub);

	printf("\nInsertionSort\t\t", "");
	for (i = 0; i < 10; i++)
	{
		start = clock();
		mainIns(  a,   lb,  ub);
		diff = clock() - start;
		msec = diff * 1000 / CLOCKS_PER_SEC;
		printf("\t\t%d.%d", msec/1000, msec%1000);
	}


	printf("\nQuickSort\t\t", "");
	for (i = 0; i < 10; i++)
	{
		start = clock();
		mainQSort( a,   lb,  ub );
		diff = clock() - start;
		msec = diff * 1000 / CLOCKS_PER_SEC;
		printf("\t\t%d.%d", msec/1000, msec%1000);
	}

	printf("\nQuickSortEnhanced\t\t", "");
	for (i = 0; i < 10; i++)
	{	
		start = clock();
		mainQui(  a,   lb,  ub);
		diff = clock() - start;
		msec = diff * 1000 / CLOCKS_PER_SEC;
		printf("\t\t%d.%d", msec/1000, msec%1000);
	}
	if(maxnum<=2000){
		printf("\nQuickSortLinkedList\t\t", "");
		for (i = 0; i < 10; i++)
		{	
			start = clock();
			mainQuiList( a,   lb,  ub);
			diff = clock() - start;
			msec = diff * 1000 / CLOCKS_PER_SEC;
			printf("\t\t%d.%d", msec/1000, msec%1000);
		}
	}
	printf("\nShellSort\t\t", "");
	for ( i = 0; i < 10; i++)
	{	
		start = clock();
		mainShl(  a,   lb,  ub );
		diff = clock() - start;
		msec = diff * 1000 / CLOCKS_PER_SEC;
		printf("\t\t%d.%d", msec/1000, msec%1000);
	}

	return 0;
}