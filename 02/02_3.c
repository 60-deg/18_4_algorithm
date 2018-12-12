#include "Item3.h"
#include "STACK.h"
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
	s[maxN] = LIMIT;
}

int STACKempty() {
	return N == 0;
}

void STACKpush(Item item) {
	if (eq(s[N], LIMIT)) {
		STACKerror();
	}
	copy(s[N], item);
	N++;
	return;
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

void STACKfree() {
	for (int i = 0; i < N; i++) {
		itemfree(s[N]);
	}
	free(s);
}

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
			while (isnum(c)) {
				num *= 10;
				num += c - '0';
				if (scanf("%c", &c) == EOF) {
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