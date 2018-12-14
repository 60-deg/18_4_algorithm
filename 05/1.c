#include "item.h"
#include "key.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct STnode *link;
struct STnode {
	Item item;
	link next;
};
static link *heads, z;
static int N, M;

static link NEW(Item item, link next) {
	link x = (link)malloc(sizeof *x);
	x->item = item;
	x->next = next;
	return x;
}

Item searchR(link l, Key v) {
	printf("searchR v:%d\n", v);
	if (eq(key(l->item), v)) {
		// 見ているノードのitemについて，key(item) が v
		// と一致するなら，itemを返す
		return l->item;
	} else {
		//  そうでなければ，次のノードへ探索を進める
		return searchR(l->next, v);
	}
}

int has(Key v, int M) {
	printf("has v:%d\n", v);
	return hash(v) % M;
}

void STinit(int max) {
	int i;

	N = 0;
	M = max / 5;
	heads = malloc(M * sizeof(link));
	z = NEW(NULLitem, NULL);
	for (i = 0; i < M; i++) {
		heads[i] = z;
	}
}

void STinsert(Item item) {
	int i = hash(key(item));
	heads[i] = NEW(item, heads[i]);
	N++;
}

Item STsearch(Key v) {
	printf("v: %d\n", v);
	if (has(v, M) < 0) {
		return NULLitem;
	}
	return searchR(heads[has(v, M)], v);
}

int STcount() {
	return N;
}

int main(void) {
	Item item;
	Key x;
	int max = 10;

	STinit(max);

	for (int i = 0; i < max; i++) {
		printf("insert (item) : ");
		scanf("%d", &x);
		STinsert(x);
	}

	for (int i = 0; i < max / 2; i++) {
		printf("search (key) : ");
		scanf("%d", &x);
		item = STsearch(x);
		if (eq(item, NULLitem)) {
			printf("item not found\n");
		} else {
			printf("found! item: %d\n", item);
		}
	}

	return 0;
}
