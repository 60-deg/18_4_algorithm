#include <stdio.h>
#include <stdlib.h>

// interface

typedef struct QUEUEnode *Qlink;

struct QUEUEnode {
	int item;
	Qlink next;
};

static Qlink head;
static Qlink tail;

void QUEUEerror();
Qlink QNEW(int item);
void QUEUEenqueue(int item);
int QUEUEdequeue();
void QUEUEfree();
int QUEUEempty();

void QUEUEerror() {
	printf("QUEUEerror\n");
	QUEUEfree();
	exit(1);
}

Qlink QNEW(int item) {
	Qlink x = (Qlink)malloc(sizeof *x);
	if (x == NULL) {
		QUEUEerror();
	}
	x->item = item;
	x->next = NULL;
	return x;
}

// implementation

void QUEUEenqueue(int item) {
	if (head == NULL) {
		head = (tail = QNEW(item));
		return;
	}
	tail->next = QNEW(item);
	tail = tail->next;
	tail->next = NULL;
	return;
}

int QUEUEdequeue() {
	int ret;
	Qlink x = head;
	if (x == NULL) {
		QUEUEerror();
	}
	ret = x->item;
	head = x->next;
	free(x);
	return ret;
}

void QUEUEfree() {
	Qlink tmp;
	while (head != NULL) {
		tmp = head;
		head = head->next;
		free(tmp);
	}
	return;
}

int QUEUEempty() {
	return head == NULL ? 1 : 0;
}

// client

// int main() {
// 	int n, i;

// 	printf("push N items to queue\nN: ");
// 	scanf("%d", &n);
// 	for (i = 0; i < n; i++) {
// 		QUEUEenqueue(i);
// 	}

// 	printf("pop N items from queue\nN: ");
// 	scanf("%d", &n);
// 	for (i = 0; i < n; i++) {
// 		printf("%d\n", QUEUEdequeue());
// 	}

// 	QUEUEfree();

// 	return 0;
// }