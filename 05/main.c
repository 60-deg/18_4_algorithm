#include "item.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static Item *pq;
static int N;

void fixUp(Item a[], int k) {
	while (k >= 1 && less(a[k], a[(k - 1) / 2])) {
		// do something
		exch(a[k], a[(k - 1) / 2]);
		k--;
	}
}

void fixDown(Item a[], int k, int N) {
	// do something
	if (2 * k + 1 > N) {
		return;
	}
	if (2 * k + 2 > N) {
		exch(a[k], a[2 * k + 1]);
		return;
	}
	int l = a[2 * k + 1] <= a[2 * k + 2] ? 2 * k + 1 : 2 * k + 2;
	exch(a[k], a[l]);
	fixDown(a, l, N);
}

Item PQdelmin(void) {
	exch(pq[1], pq[N]);
	fixDown(pq, 1, N - 1);
	return pq[N--];
}

void PQinit(int maxN) {
	pq = malloc((maxN + 1) * sizeof(Item));
	N = 0;
}

int PQempty(void) {
	return N == 0;
}

void PQinsert(Item v) {
	pq[++N] = v;
	fixUp(pq, N);
}

int main(int argc, char *argv[]) {
	int N, i, num;
	int a[] = {7, 3, 1, 5, 9};

	srand(time(NULL));

	N = atoi(argv[1]);
	PQinit(N);
	printf("Insert: ");
	for (i = 0; i < N; i++) {
		num = (rand() % 11);
		printf("%d ", num);
		PQinsert(num);
	}
	printf("\n");

	for (i = 0; i < N; i++) {
		printf("%d ", a[i]);
	}

	for (i = 0; i < (sizeof(a) / sizeof(a[0])); i++) {
		printf("Extract: %d ", PQdelmin());
		printf("Insert: %d\n", a[i]);
		PQinsert(a[i]);
	}

	printf("Extract: %d\n", PQdelmin());
	return 0;
}
