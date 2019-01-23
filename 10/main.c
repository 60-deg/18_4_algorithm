// 隣接行列を使う場合
// #include "adjMatrix.h"

// 隣接リストを使う場合
// #include "adjList.h"

int main(int argc, char *argv[]) {
	printf("graphType: %s\n", graphType);

	int V = atoi(argv[1]), E = atoi(argv[2]);
	Graph G = GRAPHrand(V, E);
	GRAPHshow(G);

	int v, w;
	printf("add Edge: ");
	scanf("%d %d", &v, &w);
	GRAPHinsertE(G, EDGE(v, w));
	GRAPHshow(G);

	printf("remove Edge: ");
	scanf("%d %d", &v, &w);
	GRAPHremoveE(G, EDGE(v, w));
	GRAPHshow(G);
}