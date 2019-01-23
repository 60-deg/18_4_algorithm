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
