#include "item1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	if (l->next == NULL) {
		return NULL;
	} else if (strcmp((l->item)->keyVal, v) == 0) {
		// 見ているノードのitemについて，item->key が v と一致するなら，itemを返す
		return l->item;
	} else {
		//  そうでなければ，次のノードへ探索を進める
		return searchR(l->next, v);
	}
}

int hashU(char *v, int M) {
	int h, a = 31415, b = 27183;
	for (h = 0; *v != '\0'; v++, a = a * b % (M - 1)) {
		h = (a * h + *v) % M;
	}
	return h;
}

void STinit(int max) {
	int i;
	N = 0;
	M = max / 5;
	heads = malloc(max * sizeof(link));
	z = NEW(NULLitem, NULL);
	for (i = 0; i < M; i++) {
		heads[i] = z;
	}
}

void STinsert(Item item) {
	int i = hashU(key(item), M);
	heads[i] = NEW(item, heads[i]);
	N++;
}

Item STsearch(Key v) {
	if (hashU(v, M) < 0 || hashU(v, M) >= M) {
		return NULL;
	}
	return searchR(heads[hashU(v, M)], v);
}

int STcount() {
	return N;
}

int main(void) {
	Item item;
	int x;
	Key y;
	int max = 10;

	STinit(max);

	for (int i = 0; i < max; i++) {
		Item newitem = (Item)malloc(sizeof(*newitem));
		newitem->keyVal = (char *)malloc(max * (sizeof(char)));
		Key y = (char *)malloc(max * (sizeof(char)));
		printf("insert (item) : ");
		scanf("%d", &x);
		printf("insert (key) : ");
		scanf("%s", y);
		newitem->value = x;
		strcpy(newitem->keyVal, y);
		STinsert(newitem);
	}

	for (int i = 0; i < max / 2; i++) {
		Key y = (char *)malloc(max * (sizeof(char)));
		printf("search (key) : ");
		scanf("%s", y);
		item = STsearch(y);
		if (item == NULL) {
			printf("item not found\n");
		} else {
			printf("found! item: %d\n", item->value);
		}
	}

	return 0;
}
