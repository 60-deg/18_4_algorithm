#include "header.h"

int partition(Item a[], int l, int r) {
	printf("l=%d, r=%d\n", l, r);
	int i = l, j = r - 1;
	Item v = a[r - 1]; // pivot
	for (;;) {
		while (less(a[++i], v))
			;
		while (less(v, a[--j])) {
			if (j == l) {
				break;
			}
			if (i >= j) {
				break;
			}
			exch(a[i], a[j]);
		}
	}
	exch(a[i], a[r - 1]);
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