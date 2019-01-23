#include "adjMatrix.h"

int *visited;
const char *searchAlgorithm = "DFS";

void search(Graph G, int x) {
	visited[x] = 1;
	printf(" %2d", x);
	for (int v = 0; v < G->V; v++) {
		if (!visited[v] && G->adj[x][v]) {
			search(G, v);
		}
	}
}