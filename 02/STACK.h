#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// interface
static Item *s;
static int N;

void STACKerror();
void STACKinit(int maxN);
int STACKempty();
void STACKpush(Item item);
Item STACKpop();
void STACKprint();
void STACKfree();

void STACKerror() {
	printf("STACKerror\n");
	free(s);
	exit(1);
}

// implementation

void STACKinit(int maxN) {
	// メモリを確保してサイズmaxNのスタックを用意する
	s = (Item *)malloc((maxN + 1) * sizeof(Item));
	if (s == NULL) {
		STACKerror();
	}
	N = 0;
	s[maxN] = LIMIT;
}

int STACKempty() {
	return N == 0;
}

void STACKpush(Item item) {
	// スタックトップの上 (s[N]) に新しいitemをプッシュする
	if (eq(s[N], LIMIT)) {
		STACKerror();
	}
	copy(s[N], item);
	N++;
	return;
}

Item STACKpop() {
	// スタックトップ (s[N-1]) にあるitemをポップして返す
	Item ret;
	if (N == 0) {
		STACKerror();
	}
	--N;
	ret = s[N];
	return ret;
}

void STACKprint() {
	// スタックに積まれているitemを出力する
	printf("stack: |");
	for (int i = 0; i < N; i++) {
		printf(itemformat, s[i]);
		printf("|");
	}
	printf("\n");
	return;
}

void STACKfree() {
	// スタックの各セルに積まれているitemのメモリと、スタックの各セルのメモリを解放する
	for (int i = 0; i < N; i++) {
		itemfree(s[N]);
	}
	free(s);
}