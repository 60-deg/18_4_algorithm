#include "header.h"

Item aux[maxN];
void merge(Item a[], int l, int m, int r) {
	int i, j, k;
	for (i = m + 1; i > l; i--) {
		aux[i - 1] = a[i - 1];
	}
	for (j = m; j < r; j++) {
		aux[r + m - j] = a[j + 1];
	}

	for (k = 0; k <= r; k++) {
		if (less(aux[i], aux[j])) {
			a[k] = aux[i++];
		} else {
			a[k] = aux[j--];
		}
	}
}

void sort(Item a[], int l, int r) {
	int m = (r + 1) / 2;
	if (r <= 1) return;
	sort(a, l, m);
	sort(a, m + 1, r);
	merge(a, l, m, r);
}