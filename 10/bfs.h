#include "adjList.h"
#include "queue.h"

int *visited;
const char *searchAlgorithm = "BFS";

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