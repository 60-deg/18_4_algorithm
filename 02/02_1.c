#include "Item.h"
#include "STACK.h"
#include <stdio.h>
#include <stdlib.h>

// interface
static Item *s;
static int N;

void STACKerror();
void STACKinit(int maxN);
int STACKempty();
void STACKpush(Item item);
Item STACKpop();

void STACKerror() {
	printf("STACKerror\n");
	free(s);
	exit(1);
}

// implementation

void STACKinit(int maxN) {
	s = (Item *)malloc((maxN + 1) * sizeof(Item));
	if (s == NULL) {
		STACKerror();
	}
	N = 0;
	s[maxN] = -1;
}

int STACKempty() {
	return N == 0;
}

void STACKpush(Item item) {
	if (s[N] == -1) {
		STACKerror();
	}
	s[N++] = item;
}

Item STACKpop() {
	Item ret;
	if (N == 0) {
		STACKerror();
	}
	--N;
	ret = s[N];
	s[N] = 0;
	return ret;
}

// client

int main() {
	int i, n;
	scanf("%d", &n);

	STACKinit(n);

	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		STACKpush(i);
	}
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		printf("%d ", STACKpop());
	}
	printf("\n");
	free(s);
	return 0;
}