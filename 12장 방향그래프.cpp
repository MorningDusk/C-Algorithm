/*
[ 문제 1 ] (위상순서 찾기) 주어진 방향그래프 G에 대해 다음과 같이 수행하는 프로그램을 작성하라. 
1) G가 방향 비싸이클 그래프(directed acyclic graph: DAG)면 위상순서(topological order)를 구해 인쇄. 
2) G에 방향 싸이클(directed cycle)이 존재하면 위상순서를 구할 수 없으므로 0을 인쇄.
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct incidence {
	int elem;
	struct incidence *next;
}I;

typedef struct edge {
	int start, end;
}E;

typedef struct vertex {
	char name;
	int degree;
	I *inEdge, *outEdge;
}V;

typedef struct graph {
	E *edges;
	V *vertices;
}G;

G graph;
int n, m, start, end, topOrder[100], queue[100];

void initGraph() {
	graph.vertices = (V*)malloc(sizeof(V) * 100);
	graph.edges = (E*)malloc(sizeof(E) * 1000);
}

void insertVertex(char vName, int i) {
	graph.vertices[i].name = vName;
	graph.vertices[i].inEdge = (I*)malloc(sizeof(I));
	graph.vertices[i].inEdge->next = NULL;
	graph.vertices[i].outEdge = (I*)malloc(sizeof(I));
	graph.vertices[i].outEdge->next = NULL;
	graph.vertices[i].degree = 0;
}

int index(char vName) {
	int i;
	for (i = 0; i < n; i++)
		if (graph.vertices[i].name == vName)
			return i;
}

void addFirst(I *H, int i) {
	I *node = (I*)malloc(sizeof(I));
	node->elem = i;
	node->next = H->next;
	H->next = node;
}

void insertDirectedEdge(char uName, char wName, int i) {
	int u, w;
	u = index(uName);
	w = index(wName);
	graph.edges[i].start = u;
	graph.edges[i].end = w;
	addFirst(graph.vertices[u].outEdge, i);
	addFirst(graph.vertices[w].inEdge, i);
	graph.vertices[w].degree++;
}

void initQueue() {
	int i = 0;
	start = 0;
	end = 0;
	for (i = 0; i < 100; i++)
		queue[i] = 0;
}

int isEmpty() {
	if (start == end)
		return 1;
	else
		return 0;
}

void enqueue(int v) {
	queue[end] = v;
	end = (end + 1) % 100;
}

int dequeue() {
	int v = queue[start];
	start = (start + 1) % 100;
	return v;
}

void topologicalSort() {
	int in[100];
	int i, t = 1, u, w;
	I *e;
	initQueue();
	for (i = 0; i < n; i++) {
		in[i] = graph.vertices[i].degree;
		if (in[i] == 0)
			enqueue(i);
	}
	while (!isEmpty()) {
		u = dequeue();
		topOrder[t] = u;
		t += 1;
		e = graph.vertices[u].outEdge;
		e = e->next;
		while (e != NULL) {
			w = graph.edges[e->elem].end;
			in[w] -= 1;
			if (in[w] == 0)
				enqueue(w);
			e = e->next;
		}
	}
	if (t <= n)
		topOrder[0] = 0;
	else
		topOrder[0] = 1;
}

void buildGraph() {
	char vName, uName, wName;
	int i;
	initGraph();
	scanf("%d", &n);
	getchar();
	for (i = 0; i < n; i++) {
		scanf("%c", &vName);
		getchar();
		insertVertex(vName, i);
	}
	scanf("%d", &m);
	getchar();
	for (i = 0; i < m; i++) {
		scanf("%c %c", &uName, &wName);
		getchar();
		insertDirectedEdge(uName, wName, i);
	}
}

int main() {

	int i;
	buildGraph();
	topologicalSort();
	if (topOrder[0] == 0)
		printf("0\n");
	else {
		for (i = 1; i <= n; i++)
			printf("%c ", graph.vertices[topOrder[i]].name);
	}
	return 0;
}