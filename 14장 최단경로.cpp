/*
[ 문제 1 ] (무방향 양의 가중그래프에서 최단거리 찾기) 무방향 양의 가중그래프(undirected weighted graph) G와 출발정점이 주어지면, 출발정점에서 다른 모든 정점으로 가는 최단거리를 구하는 프로그램을 작성하라. 
입력 그래프의 성질:
◦ n(1 ≤ n ≤ 100)개의 정점과 m(1 ≤ m ≤ 1,000)개의 간선으로 구성.
◦ 정점은 1 ~ n 사이의 정수로 번호가 매겨져 있고, 정점의 번호는 모두 다름.
◦ 모든 간선은 무방향간선이다.
*/

#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

typedef struct edge {
	struct edge* before;
	struct edge* next;
	int u;
	int v;
	int d;
}edge;


typedef struct vertex {
	edge* edge;
	int vertex;
	int d;
}vertex;

typedef struct Sack {
	int vertex;
	int d;
}Sack;

int j, k, s, p;
vertex* Q;

void downHeap(vertex* Q, int i, int p) {
	int left, right, tmpn, dtmp, vtmp;
	left = 2 * i; right = 2 * i + 1;
	vertex* tmp;
	struct edge* etmp;


	if (left > p)
		return;
	tmpn = left;

	if (right <= p) {
		if (Q[right].d < Q[tmpn].d) {
			tmpn = right;
		}
	}
	if (Q[i].d < Q[tmpn].d)
		return;

	tmp = &Q[i];
	vtmp = Q[i].vertex;
	dtmp = Q[i].d;
	etmp = Q[i].edge;

	Q[i] = Q[tmpn];

	Q[tmpn].vertex = vtmp;
	Q[tmpn].d = dtmp;
	Q[tmpn].edge = etmp;

	downHeap(Q, tmpn, p);

}

void buildHeap(vertex* Q, int p) {
	int i;
	for (i = p / 2; i >= 1; i--)
		downHeap(Q, i, p);
}

void create_vertex(vertex *v) {
	int i;
	for (i = 0; i < j; i++) {
		v[i].vertex = i + 1;
		v[i].edge = (edge*)malloc(sizeof(edge));
		v[i].edge->next = NULL;
		v[i].edge->before = NULL;
	}
}

void add_edge(vertex *vertices, int u, int v, int distance) {
	edge* tmp;
	tmp = (edge*)malloc(sizeof(edge));
	tmp->next = NULL;


	while (vertices[u - 1].edge->next != NULL)
		vertices[u - 1].edge = vertices[u - 1].edge->next;
	vertices[u - 1].edge->u = u;
	vertices[u - 1].edge->v = v;
	vertices[u - 1].edge->d = distance;

	vertices[u - 1].edge->next = tmp;
	tmp->before = vertices[u - 1].edge;

	while (vertices[u - 1].edge->before != NULL)
		vertices[u - 1].edge = vertices[u - 1].edge->before;

}

void Dijkstra(vertex *v) {
	Sack* sack;
	int i = 0, check = 0;
	vertex* u, *z;

	for (i = 0; i < j; i++) {
		v[i].d = 30000;
	}
	v[s - 1].d = 0;

	Q = (vertex*)malloc((j + 1) * sizeof(vertex));
	sack = (Sack*)malloc(j * sizeof(Sack));

	for (i = 1; i <= j; i++) {
		Q[i] = v[s - 1];
		s++;
		if (s == j + 1)
			s = 1;
	}p = j; i = 0;


	u = (vertex*)malloc(sizeof(vertex));

	while (p != 0) {
		u->d = Q[1].d;
		u->edge = Q[1].edge;
		u->vertex = Q[1].vertex;
		sack[Q[1].vertex - 1].vertex = Q[1].vertex;
		sack[Q[1].vertex - 1].d = Q[1].d;

		Q[1] = Q[p];
		p--;


		buildHeap(Q, p);

		while (u->edge->next != NULL) {

			z = &v[u->edge->v - 1];

			for (i = 1; i <= p; i++) {
				if (z->vertex == Q[i].vertex) {
					check++;
					break;
				}
			}
			if (check == 1) {
				if (u->d + u->edge->d < z->d) {
					z->d = u->d + u->edge->d;
					Q[i].d = z->d;
					buildHeap(Q, p);
				}
			}
			u->edge = u->edge->next;

			check = 0;
		}


	}

	for (int i = 0; i < j; i++) {
		if (sack[i].d != 0 && sack[i].d != 30000)
			printf("%d %d\n", sack[i].vertex, sack[i].d);
	}

}

int main() {
	int u, v, d, i;
	vertex* vertices; edge* e;

	scanf("%d %d %d", &j, &k, &s);

	vertices = (vertex*)malloc(j * sizeof(vertex));

	create_vertex(vertices);


	for (i = 0; i < k; i++) {
		scanf("%d %d %d", &u, &v, &d);
		add_edge(vertices, u, v, d);
		add_edge(vertices, v, u, d);
	}


	Dijkstra(vertices);

}

/*
[ 문제 2 ] (방향 가중그래프에서 최단거리 찾기) 방향 가중그래프(directed weighted graph) G와 출발정점이 주어지면, 출발정점에서 다른 모든 정점으로 가는 최단거리를 구하는 프로그램을 작성하라. 
입력 그래프의 성질:
◦ n(1 ≤ n ≤ 100)개의 정점과 m(1 ≤ m ≤ 1,000)개의 간선으로 구성. 
◦ 정점은 1 ~ n 사이의 정수로 번호가 매겨져 있고, 정점의 번호는 모두 다름. 
◦ 모든 간선은 방향간선이고, 무게를 가진다(음의 가중치도 허용).
◦ 음의 사이클을 가지는 그래프는 입력되지 않는다고 가정.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct incidence {
	int elem;
	struct incidence *next;
}I;

typedef struct vertex {
	int name, distance, degree;
	I *inEdge, *outEdge;
}V;

typedef struct edge {
	int start, end, weight;
}E;

typedef struct graph {
	V *vertices;
	E *edge;
}G;

G graph;
int n, m, s;

void buildGraph();
void insertVertex(int i);
void insertIncidentEdge(int uName, int wName, int i, int weight);
int index(int vName);
void addFirst(I* H, int i);
void BellmanFordShortestPaths();

int main() {

	buildGraph();
	BellmanFordShortestPaths();

}

void buildGraph() {
	int i, weight, v1, v2;
	scanf("%d %d %d", &n, &m, &s);
	graph.vertices = (V*)malloc(sizeof(V)*n);
	graph.edge = (E*)malloc(sizeof(E)*m);
	for (i = 0; i < n; i++)
		insertVertex(i);
	for (i = 0; i < m; i++) {
		scanf("%d %d %d", &v1, &v2, &weight);
		insertIncidentEdge(v1, v2, i, weight);
	}
}

void insertVertex(int i) {
	graph.vertices[i].name = i + 1;
	graph.vertices[i].inEdge = (I*)malloc(sizeof(I)*n);
	graph.vertices[i].inEdge->next = NULL;
	graph.vertices[i].outEdge = (I*)malloc(sizeof(I)*n);
	graph.vertices[i].outEdge->next = NULL;
	graph.vertices[i].degree = 0;
}

void insertIncidentEdge(int v1, int v2, int i, int weight) {
	int u, v;
	u = index(v1);
	v = index(v2);
	graph.edge[i].start = u;
	graph.edge[i].end = v;
	graph.edge[i].weight = weight;
	addFirst(graph.vertices[u].outEdge, i);
	addFirst(graph.vertices[v].inEdge, i);
	graph.vertices[v].degree++;
}

int index(int u) {
	int i;
	for (i = 0; i < n; i++)
		if (graph.vertices[i].name == u)
			return i;
}

void addFirst(I *H, int i) {
	I *p = (I*)malloc(sizeof(I));
	p->elem = i;
	p->next = H->next;
	H->next = p;
}

void BellmanFordShortestPaths() {
	int u, z, i, j;
	for (i = 0; i < n; i++)
		graph.vertices[i].distance = 100000;
	graph.vertices[s - 1].distance = 0;
	for (i = 1; i <= n; i++)
		for (j = 0; j < m; j++) {
			u = graph.edge[j].start;
			z = graph.edge[j].end;
			if (graph.vertices[z].distance > graph.vertices[u].distance + graph.edge[j].weight && graph.vertices[u].distance != 100000)
				graph.vertices[z].distance = graph.vertices[u].distance + graph.edge[j].weight;
		}
	for (i = 0; i < n; i++)
		if (graph.vertices[i].distance != 100000 && graph.vertices[i].name != s)
			printf("%d %d\n", graph.vertices[i].name, graph.vertices[i].distance);
}