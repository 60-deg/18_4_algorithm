## アルゴリズムとデータ構造 第3回レポート

17B16210 山根初美

### 1-1. ハッシュの実装 (分離連鎖法)

#### ソースコード

##### item1.h

```c
typedef char *Key;
struct record {
	Key keyVal;
	int value;
};
typedef struct record *Item;

#define maxN 1000
#define maxKey 100
#define NULLitem NULL
#define key(itemx) itemx->keyVal
```

##### 1.c

```c
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


```

##### 実行結果

![スクリーンショット 2018-12-19 14.55.37](/Users/hatsumi/Desktop/スクリーンショット 2018-12-19 14.55.37.png)





###2. ヒープの実装

####ソースコード

##### item2.h 

```c
typedef char *Key;
struct record {
	Key keyVal;
	int value;
};
typedef struct record *Item;

#define maxN 1000
#define maxKey 100
#define NULLitem NULL
#define eq(x, y) x->value == y->value // x, y はItem
```



##### 2.c

```c
#include "item2.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static Item *pq;
static int N;

void fixUp(Item a[], int k) {
	while (k > 1 && less(a[k], a[k / 2])) {
		// do something
		exch(a[k], a[k / 2]);
		k = k / 2;
	}
}

void fixDown(Item a[], int k, int N) {
	// do something
	if (2 * k > N) {
		return;
	}
	if (2 * k + 1 > N) {
		exch(a[k], a[2 * k]);
		return;
	}
	int l = a[2 * k] <= a[2 * k + 1] ? 2 * k : 2 * k + 1;
	exch(a[k], a[l]);
	fixDown(a, l, N);
}

Item PQdelmin(void) {
	exch(pq[1], pq[N]);
	fixDown(pq, 1, N - 1);
	return pq[N--];
}

void PQinit(int maxN) {
	pq = malloc((maxN + 1) * sizeof(Item));
	N = 0;
}

int PQempty(void) {
	return N == 0;
}

void PQinsert(Item v) {
	pq[++N] = v;
	fixUp(pq, N);
}

int main(int argc, char *argv[]) {
	int N, i, num;
	int a[] = {7, 3, 1, 5, 9};

	srand(time(NULL));

	N = atoi(argv[1]);
	PQinit(N);
	printf("Insert: ");
	for (i = 0; i < N; i++) {
		num = (rand() % 11);
		printf("%d ", num);
		PQinsert(num);
	}
	printf("\n");

	for (i = 0; i < (sizeof(a) / sizeof(a[0])); i++) {
		printf("Extract: %d ", PQdelmin());
		printf("Insert: %d\n", a[i]);
		PQinsert(a[i]);
	}

	printf("Extract: %d\n", PQdelmin());
	return 0;
}

```



#### 実行結果

![スクリーンショット 2018-12-19 13.03.33](/Users/hatsumi/Desktop/スクリーンショット 2018-12-19 13.03.33.png)