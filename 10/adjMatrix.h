#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

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
