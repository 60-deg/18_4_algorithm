#include "merge.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
	int i, N, sw;
	int *a;
	clock_t c1, c2;

	srand(time(NULL));
	if (argc < 3) {
		printf("You have not entered enough arguments: N and sw required!\n ");
	} else {
		N = atoi(argv[1]);
		sw = atoi(argv[2]);
		a = malloc(N * sizeof(int));
		if (sw) {
			for (i = 0; i < N; i++) a[i] = 100000 * (1.0 * rand() / RAND_MAX);
		} else {
			while (scanf("%d", &a[N]) == 1) N++;
		}

		printf("Initial: ");
		for (i = 0; i < N; i++) printf("%3d ", a[i]);
		printf("\nAfter: ");

		c1 = clock();
		sort(a, 0, N - 1);
		c2 = clock();

		for (i = 0; i < N; i++) printf("%3d ", a[i]);
		printf("\n");

		printf("time = %f[s]\n", (double)(c2 - c1) / CLOCKS_PER_SEC);
	}
	return 0;
}
