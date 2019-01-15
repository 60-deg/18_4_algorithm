#include "header.h"
// #include <stdio.h>

// void printList(Item lst[]) {
// 	int n = 10;
// 	for (int i = 0; i < n; i++) {
// 		printf("%d ", lst[i]);
// 	}
// 	printf("\n");
// 	return;
// }

void merge(Item a[], int l, int m, int r) {
	Item aux[maxN] = {};
	// 配列aの左半分 [l, m] と右半分 [m+1, r] をマージする
	for (int i = l; i <= m; i++) {
		// 左半分をauxの左半分に昇順でコピー
		aux[i] = a[i];
	}
	for (int i = m; i < r; i++) {
		// 右半分をauxの右半分に降順でコピー
		aux[r + m - i] = a[i + 1];
	}

	int i = l, j = r;
	for (int k = l; k <= r; k++) {
		if (less(aux[i], aux[j])) {
			a[k] = aux[i++];
		} else {
			a[k] = aux[j--];
		}
	}
}

void sort(Item a[], int l, int r) {
	int m = (r + l) / 2;
	if (r <= l) return;
	sort(a, l, m);	 // 左半分 [l, m] をソート
	sort(a, m + 1, r); // 右半分 [m+1, r] をソート
	merge(a, l, m, r); // マージ
}