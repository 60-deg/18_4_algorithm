#include "Item1.h"
#include "STACK.h"

// client

int main() {
	int i, n;

	printf("stack size: ");
	scanf("%d", &n);

	STACKinit(n);

	printf("push N items to stack\nN: ");
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		STACKpush(i);
	}
	STACKprint();

	printf("pop N items from stack\nN: ");
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		printf("pop %d\n", STACKpop());
	}
	STACKprint();

	STACKfree();
	return 0;
}