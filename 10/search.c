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