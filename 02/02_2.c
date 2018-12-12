#include "Item2.h"
#include <stdio.h>
#include <stdlib.h>

// interface

typedef struct QUEUEnode *link;

struct QUEUEnode {
	Item item;
	link next;
};

static link head;
static link tail;

void QUEUEerror();
link NEW(Item item);
void QUEUEenqueue(Item item);
Item QUEUEdequeue();
void QUEUEfree();

void QUEUEerror() {
	printf("QUEUEerror\n");
	QUEUEfree();
	exit(1);
}

link NEW(Item item) {
	link x = (link)malloc(sizeof *x);
	if (x == NULL) {
		QUEUEerror();
	}
	x->item = item;
	x->next = NULL;
	return x;
}

// implementation

void QUEUEenqueue(Item item) {
	if (head == NULL) {
		head = (tail = NEW(item));
		return;
	}
	tail->next = NEW(item);
	tail = tail->next;
	tail->next = NULL;
	return;
}

Item QUEUEdequeue() {
	Item ret;
	link x = head;
	if (x == NULL) {
		QUEUEerror();
	}
	ret = x->item;
	head = x->next;
	free(x);
	return ret;
}

void QUEUEfree() {
	link tmp;
	while (head != NULL) {
		tmp = head;
		head = head->next;
		free(tmp);
	}
	return;
}

// client

int main() {
	int n, i;

	printf("push N items to queue\nN: ");
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		QUEUEenqueue(i);
	}

	printf("pop N items from queue\nN: ");
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		printf("%d\n", QUEUEdequeue());
	}

	QUEUEfree();

	return 0;
}