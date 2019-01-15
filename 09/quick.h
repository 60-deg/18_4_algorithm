#include "header.h"
// #include <stdio.h>

// void printA(Item a[]) {
// 	for (int i = 0; i < 10; i++) {
// 		printf("%d ", a[i]);
// 	}
// 	printf("\n");
// }

int partition(Item a[], int l, int r) {
	// 配列a を，pivotより小さいものが l〜i-1, pivotより大きいものが i+1〜r
	// に入っているように整理して，iを返す
	Item v = a[r]; // pivot
	int i = l;
	while (less(a[i], v)) {
		i++;
		if (i == r) {
			return i;
		}
	}
	for (int j = r - 1; j >= i; j--) {
		if (less(a[j], v)) {
			exch(a[i], a[j]);
			while (less(a[i], v) && j >= i) {
				i++;
			}
		}
	}
	exch(a[i], a[r]);
	// printf("l: %d, r:%d, i: %d\n", l, r, i);
	// printA(a);
	return i;
}

void sort(Item a[], int l, int r) {
	int i;
	if (r <= l) {
		return;
	}
	i = partition(a, l, r);
	sort(a, l, i - 1);
	sort(a, i + 1, r);
}