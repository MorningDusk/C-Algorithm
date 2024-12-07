/*
[ 문제 1 ] (DFS) 입력으로 주어지는 그래프의 DFS 순회 결과를 출력하는 프로그램을 작성하시오. 
입력 그래프의 성질:
◦ n (1 ≤ n ≤ 100) 개의 정점과 m (1 ≤ m ≤ 1,000) 개의 간선으로 구성
◦ 정점은 1 ~ n 사이의 정수로 번호가 매겨져 있고, 정점의 번호는 모두 다름
◦ 모든 간선은 무방향 간선이고, 한 정점에서 임의의 다른 정점으로 가는 경로는 반드시 존재
구현 조건:
◦ 그래프는 인접리스트 구조를 사용하여 표현해야 한다. 
◦ 인접 정점의 조사 순서
- 정점 u의 인접 정점(or 부착 간선)들을 번호가 작은 정점부터 조사한다. 
(즉, 아래 DFS 의사 코드의 for 문(☚)에서 인접 정점들을 번호가 작은 정점부터 큰 순서대로 조사하라. 조사 순서에 따라 방문 결과가 달라질 수 있음에 유의할 것)
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct incidence {
	int edge;
	struct incidence *next;
}I;

typedef struct vertices {
	I *incidence;
	int elem, label;
}V;

typedef struct edge {
	int v1, v2, label;
}E;

typedef struct graph {
	V *vertices;
	E *edges;
	int edgeSize, size;
}G;

I *getIncidence(int edge) {
	I *node = (I*)malloc(sizeof(I));
	node->edge = edge;
	node->next = NULL;
	return node;
}

void initGraph(G *graph, int n, int m) {
	int i;
	graph->size = n;
	graph->edgeSize = 0;
	graph->vertices = (V*)malloc(sizeof(V)*(n + 1));
	graph->edges = (E*)malloc(sizeof(E)*m);
	for (i = 1; i <= graph->size; i++) {
		graph->vertices[i].elem = i;
		graph->vertices[i].incidence = NULL;
	}
}

void insertIncidence(int v1, int v2, I *incidence, G *graph) {
	E *edge = graph->edges;
	V *vertices = graph->vertices;
	I *p;
	int tmp;
	p = vertices[v1].incidence;
	if (p == NULL)
		vertices[v1].incidence = incidence;
	else {
		if (edge[p->edge].v1 == v1)
			tmp = edge[p->edge].v2;
		else
			tmp = edge[p->edge].v1;
		if (tmp > v2) {
			incidence->next = p;
			vertices[v1].incidence = incidence;
		}
		else {
			while (p->next != NULL) {
				if (edge[p->next->edge].v1 == v1)
					tmp = edge[p->next->edge].v2;
				else
					tmp = edge[p->next->edge].v1;
				if (tmp > v2)
					break;
				p = p->next;
			}
			if (p->next == NULL)
				p->next = incidence;
			else {
				incidence->next = p->next;
				p->next = incidence;
			}
		}
	}
}

void insertEdge(int v1, int v2, G *graph) {
	E *edge = graph->edges;
	I *i1, *i2;
	int i, j = -1;
	for (i = 0; i < graph->edgeSize; i++) {
		if (edge[i].v1 == v1 && edge[i].v2 == v2) {
			j = i;
			break;
		}
		if (edge[i].v1 == v2 && edge[i].v2 == v1) {
			j = i;
			break;
		}
	}
	if (j == -1)
		j = graph->edgeSize;
	edge[j].v1 = v1;
	edge[j].v2 = v2;
	i1 = getIncidence(j);
	i2 = getIncidence(j);
	insertIncidence(v1, v2, i1, graph);
	if (v1 != v2)
		insertIncidence(v2, v1, i2, graph);
	graph->edgeSize += 1;
}

void rDFS(G *graph, int s) {
	E *edge = graph->edges;
	I *ie = NULL;
	int j = s, tmp;
	printf("%d\n", j);
	graph->vertices[j].label = -1;
	ie = graph->vertices[j].incidence;
	while (ie != NULL) {
		if (graph->edges[ie->edge].label == 0) {
			if (edge[ie->edge].v1 == graph->vertices[j].elem)
				tmp = edge[ie->edge].v2;
			else
				tmp = edge[ie->edge].v1;
			if (graph->vertices[tmp].label == 0) {
				graph->edges[ie->edge].label = -1;
				rDFS(graph, tmp);
			}
		}
		ie = ie->next;
	}
}

void DFS(G *graph, int s) {
	int i;
	for (i = 1; i <= graph->size; i++)
		graph->vertices[i].label = 0;
	for (i = 0; i < graph->edgeSize; i++)
		graph->edges[i].label = 0;
	rDFS(graph, s);
}

int main() {

	G graph;
	int n, m, s, u, v, i;
	scanf("%d %d %d", &n, &m, &s);
	initGraph(&graph, n, m);
	for (i = 0; i < m; i++) {
		scanf("%d %d", &u, &v);
		insertEdge(u, v, &graph);
	}
	DFS(&graph, s);

	return 0;
}

/*
[ 문제 2 ] (BFS) 입력으로 주어지는 그래프의 BFS 순회 결과를 출력하는 프로그램을 작성하시오. 
입력 그래프의 성질:
◦ 문제 1과 동일
구현 조건:
◦ 그래프는 인접행렬 구조를 사용하여 표현해야 한다. 
◦ 인접 정점의 조사 순서
- 문제 1과 동일하게 정점의 인접 정점(or 부착 간선)들을 번호가 작은 정점부터 조사한다.
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct edge {
	int v1, v2, label;
}E;

typedef struct vertices {
	int elem, label;
}V;

typedef struct graph {
	V *vertices;
	E *edges;
	int **adjacency;
	int edgeSize, size;
}G;

void initGraph(G *graph, int n, int m) {
	int i, j;
	graph->size = 0;
	graph->edgeSize = 0;
	graph->vertices = (V*)malloc(sizeof(V)*n);
	graph->edges = (E*)malloc(sizeof(E)*m);
	graph->adjacency = (int**)malloc(sizeof(int*)*n);
	for (i = 0; i < n; i++) {
		graph->vertices[i].elem = i + 1;
		graph->vertices[i].label = -1;
		graph->adjacency[i] = (int*)malloc(sizeof(int)*n);
		for (j = 0; j < n; j++)
			graph->adjacency[i][j] = -1;
	}
	for (i = 0; i < m; i++)
		graph->edges[i].label = -1;
}

void insertEdge(int v1, int v2, G *graph) {
	E *edge = graph->edges;
	int i = 0, j = -1;
	for (i = 0; i < graph->edgeSize; i++) {
		if (edge[i].v1 == v1 && edge[i].v2 == v2) {
			j = i;
			break;
		}
		if (edge[i].v1 == v2 && edge[i].v2 == v1) {
			j = i;
			break;
		}
	}
	if (j == -1)
		j = graph->edgeSize;
	edge[j].v1 = v1;
	edge[j].v2 = v2;
	graph->adjacency[v1 - 1][v2 - 1] = j;
	graph->adjacency[v2 - 1][v1 - 1] = j;
	graph->edgeSize += 1;
}

void BFS(G *graph, int n, int m, int s) {
	int *tmp = (int*)malloc(sizeof(int)*n);
	int num = 1, cnt = 0, i;
	printf("%d\n", s);
	for (i = 0; i < n; i++)
		tmp[i] = 0;
	tmp[0] = s;
	graph->vertices[s - 1].label = 1;
	while (cnt < n) {
		for (i = 0; i < n; i++) {
			if (tmp[cnt] != 0)
				if (graph->adjacency[tmp[cnt] - 1][i] != -1 && graph->vertices[i].label == -1) {
					printf("%d\n", graph->vertices[i].elem);
					graph->vertices[i].label = 1;
					tmp[num] = i + 1;
					num++;
				}
		}
		cnt++;
	}
}

int main() {

	G graph;
	int n, m, s, u, v, i;
	scanf("%d %d %d", &n, &m, &s);
	initGraph(&graph, n, m);
	for (i = 0; i < m; i++) {
		scanf("%d %d", &u, &v);
		insertEdge(u, v, &graph);
	}
	BFS(&graph, n, m, s);

	return 0;
}