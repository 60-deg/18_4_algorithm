typedef struct {
	int v;
	int w;
} Edge;

Edge EDGE(int v, int w) {
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