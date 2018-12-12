# データ構造とアルゴリズム 第2回レポート課題

17B16210 山根初美

## 01
### ソースコード
#### STACK.h

```c
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
```

#### Item1.h

```c
typedef int Item;
#define LIMIT -1
#define eq(a, b) a == b
#define copy(x, y) x = y;
#define itemfree(x)
#define itemformat "%d"
```

#### 1.c

```c
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
```



### 実行結果

#### 正常終了

![stack](/Users/hatsumi/Documents/Titech/class/2年/4_データ構造とアルゴリズム/02/screenshots/stack.png)

#### エラー (スタックが空の時にpop)

![stackerror2](/Users/hatsumi/Documents/Titech/class/2年/4_データ構造とアルゴリズム/02/screenshots/stackerror2.png)

#### エラー (スタックが一杯の時にpush)

![stackerror1](/Users/hatsumi/Documents/Titech/class/2年/4_データ構造とアルゴリズム/02/screenshots/stackerror1.png)



## 02

### ソースコード

#### Item2.h

```c
typedef int Item;
```



#### 2.c

```c
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
```



### 実行結果

#### 正常終了

![queue](/Users/hatsumi/Documents/Titech/class/2年/4_データ構造とアルゴリズム/02/screenshots/queue.png)

#### エラー (キューが空の時にpop)

![queueerror](/Users/hatsumi/Documents/Titech/class/2年/4_データ構造とアルゴリズム/02/screenshots/queueerror.png)



## 03

#### Item3.h

```c
typedef int Item;
#define LIMIT -1
#define eq(a, b) a == b
#define copy(x, y) x = y;
#define itemfree(x)
#define itemformat "%d"
```

#### 3.c

STACK.h は[課題1のSTACK.h](#STACK.h)と同じものを使用している。

```c
#include "Item3.h"
#include "STACK.h"

// client

int isnum(char c) {
	return (c - '0' >= 0) && (c - '0' <= 9);
}

int isop(char c) {
	const char ops[4] = "+-*/";
	int i;
	for (i = 0; i < 4; i++) {
		if (ops[i] == c) {
			return 1;
		}
	}
	return 0;
}

int main() {
	// 算術式に含まれる数字と記号の数 (括弧は除く) の最大は100とする
	// 算術式全体の長さ (空白・括弧も含む) の最大は500とする
	// 異なる数値はすべて空白区切で入力されるとする
	// 括弧の有無はどちらでも良い

	int num = 0, x, y, ci;
	char c, str[500];

	STACKinit(100);
	scanf("%[^\n]s", str);

	for (ci = 0; ci < strlen(str); ci++) {
		c = str[ci];
		num = 0;
		if (c == '(' || c == ')' || c == ' ') {
			// 括弧や空白は無視
			continue;
		}
		if (isnum(c)) {
			// 数字の場合、数値全体を見終わるまでciを進めてstackに数値を積む
			int i;
			for (i = 0; isnum(c); i++) {
				num *= 10;
				num += c - '0';
				ci++;
				c = str[ci];
				if (ci >= strlen(str)) {
					break;
				}
			}
			STACKpush(num);
		}
		if (isop(c)) {
			// 演算記号の場合、stackから直前の2つの数値を取り出して演算結果をstackに積む
			y = STACKpop();
			x = STACKpop();
			switch (c) {
			case '+':
				STACKpush(x + y);
				break;
			case '-':
				STACKpush(x - y);
				break;
			case '*':
				STACKpush(x * y);
				break;
			case '/':
				STACKpush(x / y);
				break;
			}
		}
	}

	printf("%d\n", STACKpop());

	STACKfree();
	return 0;
}
```



### 実行結果

![課題3](/Users/hatsumi/Documents/Titech/class/2年/4_データ構造とアルゴリズム/02/screenshots/課題3.png)



## 04

### ソースコード

STACK.h は[課題1のSTACK.h](#STACK.h)と同じものを使用している。

#### Item4.h

```c
typedef char *Item;
#define LIMIT "LIMIT"
#define eq(x, y) (x != NULL && y != NULL && strcmp(x, y) == 0)
#define copy(x, y) x = (char *)malloc((500) * sizeof(char)); strcpy(x, y);
#define itemfree(x) free(x)
#define itemformat "%s"
```

#### 4.c

```c
#include "Item4.h"
#include "STACK.h"

// client

int isnum(char c) {
	return (c - '0' >= 0) && (c - '0' <= 9);
}

int isop(char c) {
	const char ops[4] = "+-*/";
	int i;
	for (i = 0; i < 4; i++) {
		if (ops[i] == c) {
			return 1;
		}
	}
	return 0;
}

int main() {
	// 算術式に含まれる数字と記号の数 (括弧は除く) の最大は100とする
	// 算術式全体の長さ (空白・括弧も含む) の最大は500とする
	// 異なる数値はすべて空白区切で入力されるとする
	// 括弧の有無はどちらでも良い

	char c, str[500];
	int ci;

	STACKinit(500);
	scanf("%[^\n]s", str);

	for (ci = 0; ci < strlen(str); ci++) {
		c = str[ci];
		if (c == '(' || c == ')' || c == ' ') {
			// 括弧や空白は無視
			continue;
		}
		if (isnum(c)) {
			// 数字の場合、数値全体を見終わるまでciを進めてstackに文字列を積む
			char num[500]; // 数値を文字列化してnumに格納していく
			int i;
			for (i = 0; isnum(c); i++) {
				num[i] = c;
				ci++;
				c = str[ci];
				if (ci >= strlen(str)) {
					break;
				}
			}
			num[i] = '\0';
			ci--;
			STACKpush(num);
		}
		if (isop(c)) {
			// 演算記号の場合、stackから直前の2つの数値を取り出して演算結果をstackに積む
			char *x, *y;
			y = STACKpop();
			x = STACKpop();
			char sub[4] = {' ', c, ' ', '\0'};
			char xcy[500] = "("; // 新しく追加したい文字列
			strcat(xcy, x);
			strcat(xcy, sub);
			strcat(xcy, y);
			strcat(xcy, ")");
			free(x);
			free(y);

			STACKpush(xcy);
		}
	}

	printf("%s\n", STACKpop());

	STACKfree();
	return 0;
}
```



### 実行結果

![課題4](/Users/hatsumi/Documents/Titech/class/2年/4_データ構造とアルゴリズム/02/screenshots/課題4.png)