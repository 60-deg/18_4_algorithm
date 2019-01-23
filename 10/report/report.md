# algorithm report 5

17B16210 山根初美



## 1. 隣接行列、隣接リストの実装

### ソースコード

#### main.c

隣接行列を使う場合、隣接リストを使う場合で、それぞれincludeするヘッダーファイルのコメントアウトを消す

```c
// 隣接行列を使う場合
// #include "adjMatrix.h"

// 隣接リストを使う場合
// #include "adjList.h"

int main(int argc, char *argv[]) {
	printf("graphType: %s\n", graphType);

    // グラフの生成
	int V = atoi(argv[1]), E = atoi(argv[2]);
	Graph G = GRAPHrand(V, E);
	GRAPHshow(G);

	int v, w;
    
    // 辺の追加
	printf("add Edge: ");
	scanf("%d %d", &v, &w);
	GRAPHinsertE(G, EDGE(v, w));
	GRAPHshow(G);

    // 辺の削除
	printf("remove Edge: ");
	scanf("%d %d", &v, &w);
	GRAPHremoveE(G, EDGE(v, w));
	GRAPHshow(G);
}
```



#### adjMatrix.h

```c
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char *graphType = "matrix";

struct graph {
	int V;
	int E;
	int **adj; // 隣接行列へのポインタ
};

int **MATRIXint(int h, int w, int val) {
	// 大きさh*wの行列を，値valで初期化して返す
	int **t = (int **)malloc(h * sizeof(int *));
	if (t == NULL) {
		printf("out of memory\n");
		exit(1);
	}
	for (int i = 0; i < h; i++) {
		t[i] = (int *)malloc(w * sizeof(int));
		if (t[i] == NULL) {
			printf("out of memory\n");
			exit(1);
		}
	}
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			t[i][j] = val;
		}
	}
	return t;
}

void GRAPHshow(Graph G) {
	printf("%d vertices, %d edges\n", G->V, G->E);
	for (int j = 0; j < G->V; j++) {
		printf("%2d:", j);
		for (int k = 0; k < G->V; k++) {
			if (G->adj[j][k]) {
				printf(" %2d", k);
			}
		}
		printf("\n");
	}
}

int randV(Graph G) {
	return G->V * (rand() / (RAND_MAX + 1.0));
}

Graph GRAPHrand(int V, int E) {
	Graph G = GRAPHinit(V);

	srand((unsigned int)time(NULL));

	while (G->E < E) {
		GRAPHinsertE(G, EDGE(randV(G), randV(G)));
	}
	return G;
}

Graph GRAPHinit(int V) {
	// 頂点数Vのグラフを作成して返す
	Graph G = (Graph)malloc(sizeof(Graph *));
	G->V = V;
	G->E = 0;
	G->adj = MATRIXint(V, V, 0);
	return G;
}

void GRAPHinsertE(Graph G, Edge e) {
	// グラフGに辺eを追加する
	int v = e.v, w = e.w;
	if (!G->adj[v][w]) {
		G->E += 1;
	}
	G->adj[v][w] = 1;
	G->adj[w][v] = 1;
}

void GRAPHremoveE(Graph G, Edge e) {
	// グラフGから辺eを取り除く
	int v = e.v, w = e.w;
	if (G->adj[v][w]) {
		G->E--;
	}
	G->adj[v][w] = 0;
	G->adj[w][v] = 0;
}

int GRAPHedges(Edge a[], Graph G) {
	// 配列aにグラフGの辺を格納していく、返り値は辺の総数
	int v, w, E = 0;
	for (v = 0; v < G->V; v++) {
		for (w = 0; w < G->V; w++) {
			if (G->adj[v][w]) {
				a[E++] = EDGE(v, w);
			}
		}
	}
	return E;
}
```



#### adjList.h

```c
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char *graphType = "list";

typedef struct node *link;
struct node {
	int v;
	link next;
};
struct graph {
	int V;
	int E;
	link *adj;
};

link NEW(int v, link next) {
	link x = (link)malloc(sizeof *x);
	x->v = v;
	x->next = next;
	return x;
}

void GRAPHshow(Graph G) {
	printf("%d vertices, %d edges\n", G->V, G->E);

	for (int v = 0; v < G->V; v++) {
		printf("%2d:", v);
		for (link t = G->adj[v]; t != NULL; t = t->next) {
			printf(" %2d", t->v);
		}
		printf("\n");
	}
}

int randV(Graph G) {
	return G->V * (rand() / (RAND_MAX + 1.0));
}

Graph GRAPHrand(int V, int E) {
	Graph G = GRAPHinit(V);

	srand((unsigned int)time(NULL));
	while (G->E < E) {
		GRAPHinsertE(G, EDGE(randV(G), randV(G)));
	}
	return G;
}

Graph GRAPHinit(int V) {
	Graph G = (Graph)malloc(sizeof(*G));
	G->V = V;
	G->E = 0;
	G->adj = (link *)malloc(V * sizeof(link));
	for (int v = 0; v < V; v++) {
		G->adj[v] = NULL;
	}
	return G;
}

void GRAPHinsertE(Graph G, Edge e) {
	int v = e.v, w = e.w;
	G->adj[v] = NEW(w, G->adj[v]);
	G->adj[w] = NEW(v, G->adj[w]);
	G->E++;
}

void GRAPHremoveE(Graph G, Edge e) {
	// 辺の削除
	int count = 0; // リストから削除したノード数を数える
	int a = e.v, b = e.w;
	for (int i = 0; i < 2; i++) {
		link prev = NULL;
		for (link t = G->adj[a]; t != NULL;) {
			if (t->v == b) {
				// 探している辺が見つかった場合
				count++;
				// リストのノードをつけかえる
				if (prev == NULL) {
					G->adj[a] = t->next;
				} else {
					prev->next = t->next;
				}
				prev = t;
				link tmp = t;
				t = t->next;
				free(tmp);
			} else {
				prev = t;
				t = t->next;
			}
		}

		// aとbを交換
		int tmp = a;
		a = b;
		b = tmp;
	}

	// 削除された辺の数は、隣接リストから削除されたノード数の1/2
	G->E -= count / 2;
}

int GRAPHedges(Edge a[], Graph G) {
	int E = 0;
	link t;
	for (int v = 0; v < G->V; v++) {
		for (t = G->adj[v]; t != NULL; t = t->next) {
			if (v < t->v) {
				a[E++] = EDGE(v, t->v);
			}
		}
	}
	return E;
}
```



#### graph.h

```c
typedef struct {
	int v;
	int w;
} Edge;

Edge EDGE(int v, int w) {
	// 頂点 v, w を両端点として持つEdgeを返す
	Edge e;
	e.v = v;
	e.w = w;
	return e;
}

typedef struct graph *Graph;
Graph GRAPHinit(int);
void GRAPHinsertE(Graph, Edge);
void GRAPHremoveE(Graph, Edge);
int GRAPHedges(Edge[], Graph G);
```



### 実行結果

#### 隣接行列

![matrix](/Users/hatsumi/Documents/Titech/class/2年/4_データ構造とアルゴリズム/10/report/matrix.png)



#### 隣接リスト

![list](/Users/hatsumi/Documents/Titech/class/2年/4_データ構造とアルゴリズム/10/report/list.png)



## 2. 深さ優先探索, 3. 幅優先探索

### ソースコード

#### search.c

深さ優先探索を行う場合、幅優先探索を行う場合で、それぞれincludeするヘッダーファイルのコメントアウトを消す

```c
// 幅優先探索
// #include "bfs.h"

// 深さ優先探索
// #include "dfs.h"

int main(int argc, char *argv[]) {
	printf("graphType: %s, searchAlgorithm: %s\n", graphType, searchAlgorithm);

	int V = atoi(argv[1]), E = atoi(argv[2]);
	Graph G = GRAPHrand(V, E);
	GRAPHshow(G);

	// visited配列の初期化
	visited = (int *)malloc(sizeof(int) * V);
	for (int v = 0; v < V; v++) {
		visited[v] = 0;
	}

	// グラフを走査して、連結成分ごとに [] で区切った頂点集合を出力する
	// include されているのが bfs.h の場合は幅優先探索、dfs.h の場合は深さ優先探索を用いる
	for (int v = 0; v < V; v++) {
		if (!visited[v]) {
			printf("[");
			search(G, v);
			printf("]\n");
		}
	}
}
```



#### dfs.h

```c
#include "adjMatrix.h"

const char *searchAlgorithm = "DFS";

// visited配列の定義
int *visited;

void search(Graph G, int x) {
	visited[x] = 1;
	printf(" %2d", x);
	for (int v = 0; v < G->V; v++) {
		if (!visited[v] && G->adj[x][v]) {
			search(G, v);
		}
	}
}
```



#### adjMatrix.h

問1と同じ



#### bfs.h

```c
#include "adjList.h"
#include "queue.h"

const char *searchAlgorithm = "BFS";

// visited配列の定義
int *visited;

void search(Graph G, int x) {
	visited[x] = 1;
	printf(" %2d", x);
	for (link t = G->adj[x]; t != NULL; t = t->next) {
		QUEUEenqueue(t->v);
	}
	while (!QUEUEempty()) {
		int next = QUEUEdequeue();
		if (!visited[next]) {
			search(G, next);
		}
	}
}
```



#### adjList.h

問1と同じ



#### queue.h

```c
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
```



### 実行結果

#### 深さ優先探索 (DFS)

![dfs](/Users/hatsumi/Documents/Titech/class/2年/4_データ構造とアルゴリズム/10/report/dfs.png)



#### 幅優先探索 (BFS)
![bfs](/Users/hatsumi/Documents/Titech/class/2年/4_データ構造とアルゴリズム/10/report/bfs.png)

