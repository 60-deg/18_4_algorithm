#include "item2.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static Item *pq;
static int N;

void print() {
	int p = 1;
	for (int i = 1; p <= N; i++) {
		for (int j = 0; j < p && p + j <= N; j++) {
			printf("%d ", pq[p + j]);
		}
		p *= 2;
		printf("\n");
	}
}

void fixUp(Item a[], int k) {
	while (k > 1 && less(a[k], a[k / 2])) {
		// do something
		exch(a[k], a[k / 2]);
		k = k / 2;
	}
}

void fixDown(Item a[], int k, int N) {
	// do something
	if (2 * k > N) {
		return;
	}
	if (2 * k + 1 > N) {
		exch(a[k], a[2 * k]);
		return;
	}
	int l = a[2 * k] <= a[2 * k + 1] ? 2 * k : 2 * k + 1;
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

	// print();

	for (i = 0; i < (sizeof(a) / sizeof(a[0])); i++) {
		printf("Extract: %d ", PQdelmin());
		// print();
		printf("Insert: %d\n", a[i]);
		PQinsert(a[i]);
		// print();
	}

	printf("Extract: %d\n", PQdelmin());
	return 0;
}
