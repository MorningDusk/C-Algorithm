/*
[ 문제 1 ] (Prim-Jarnik 알고리즘) 입력으로 주어지는 그래프를 Prim-Jarnik 알고리즘을 이용하여
최소신장트리(Minimum Spanning Tree, MST)를 생성하는 프로그램을 작성하고, 최소신장트리의 생성 과정과 총무게를 결과로 출력하시오. 
입력 그래프의 성질:
◦ n (1 ≤ n ≤ 100) 개의 정점과 m (1 ≤ m ≤ 1,000) 개의 간선으로 구성된다.
◦ 정점은 1 ~ n 사이의 정수로 번호가 매겨져 있고, 정점의 번호는 모두 다르다.
◦ 모든 간선은 무방향간선이고, 한 정점에서 임의의 다른 정점으로 가는 경로는 반드시 존재한다.
◦ 간선의 무게는 중복이 없는 양의 정수다.
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct incidence {
	int edge;
	struct incidence *next;
}I;

typedef struct edge {
	int vertex1, vertex2, weight;
}E;

typedef struct vertex {
	int elem, distance;
	I *head;
}V;

typedef struct graph {
	E *edge;
	V *vertex;
	int n, m;
}G;

typedef struct heap {
	int key, distance;
}H;

G graph;

void insertVertex(int i);
void initGraph(int n, int m);
void buildGraph();
void addFirst(I *head, int i);
void insertIncidentEdge(int v1, int v2, int w, int i);
void primJarnikMST();
H *buildHeap();
void upHeap(H *heap, int i);
void downHeap(H *heap, int i, int size);
void swap(H *x, H *y);
int removeMin(H *heap, int i);
int opposite(int u, int e);
int isInclude(H *heap, int i, int z);
void replaceKey(H *heap, int i, int z, int w);
void freeGraph();

int main() {

	I *head;
	buildGraph();
	primJarnikMST();
	freeGraph();

	return 0;
}

void initGraph(int n, int m) {
	int i;
	graph.n = n;
	graph.m = m;
	graph.vertex = (V*)malloc(sizeof(V)*(n + 1));
	graph.edge = (E*)malloc(sizeof(E)*m);
	for (i = 1; i <= n; i++)
		insertVertex(i);
}

void insertVertex(int i) {
	graph.vertex[i].elem = i;
	graph.vertex[i].head = (I*)malloc(sizeof(I));
	graph.vertex[i].head->next = NULL;
}

void buildGraph() {
	int i, n, m, v1, v2, w;
	scanf("%d %d", &n, &m);
	initGraph(n, m);
	for (i = 0; i < graph.m; i++) {
		scanf("%d %d %d", &v1, &v2, &w);
		insertIncidentEdge(v1, v2, w, i);
	}
}

void addFirst(I *head, int i) {
	I *node = (I*)malloc(sizeof(I));
	node->edge = i;
	node->next = head->next;
	head->next = node;
}

void insertIncidentEdge(int v1, int v2, int w, int i) {
	graph.edge[i].vertex1 = v1;
	graph.edge[i].vertex2 = v2;
	graph.edge[i].weight = w;
	addFirst(graph.vertex[v1].head, i);
	addFirst(graph.vertex[v2].head, i);
}

void primJarnikMST() {
	H *heap;
	I *p;
	int sum = 0, u, z, i;
	for (i = 1; i <= graph.n; i++)
		graph.vertex[i].distance = 100000;
	graph.vertex[1].distance = 0;
	heap = buildHeap();
	i = graph.n;
	while (i > 0) {
		u = removeMin(heap, i);
		printf(" %d", graph.vertex[u].elem);
		sum += graph.vertex[u].distance;
		p = graph.vertex[u].head->next;
		while (p != NULL) {
			z = opposite(u, p->edge);
			if (isInclude(heap, i, z) && graph.edge[p->edge].weight < graph.vertex[z].distance) {
				graph.vertex[z].distance = graph.edge[p->edge].weight;
				replaceKey(heap, i, z, graph.vertex[z].distance);
			}
			p = p->next;
		}
		i--;
	}
	printf("\n%d", sum);
	free(heap);
}

H *buildHeap() {
	H *heap = (H*)malloc(sizeof(H)*(graph.n + 1));
	int i;
	for (i = 1; i <= graph.n; i++) {
		heap[i].distance = graph.vertex[i].distance;
		heap[i].key = graph.vertex[i].elem;
	}
	for (i = graph.n / 2; i >= 1; i--)
		downHeap(heap, i, graph.n);
	return heap;
}

void upHeap(H *heap, int i) {
	if (i == 1)
		return;
	if (heap[i].distance >= heap[i / 2].distance)
		return;
	swap(heap + i, heap + i / 2);
	upHeap(heap, i / 2);
}

void downHeap(H *heap, int i, int size) {
	int left = 2 * i, right = 2 * i + 1, smaller;
	if (left > size)
		return;
	smaller = left;
	if (right <= size)
		if (heap[right].distance < heap[left].distance)
			smaller = right;
	if (heap[i].distance <= heap[smaller].distance)
		return;
	swap(heap + i, heap + smaller);
	downHeap(heap, smaller, size);
}

void swap(H *x, H *y) {
	H tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
}

int removeMin(H *heap, int i) {
	H res = heap[1];
	if (i == 0)
		return -1;
	swap(heap + 1, heap + i);
	downHeap(heap, 1, --i);
	return res.key;
}

int opposite(int u, int e) {
	if (graph.edge[e].vertex1 == u)
		return graph.edge[e].vertex2;
	else
		return graph.edge[e].vertex1;
}

int isInclude(H *heap, int i, int z) {
	int j;
	for (j = 1; j < i; j++)
		if (heap[j].key == z)
			return 1;
	return 0;
}

void replaceKey(H *heap, int i, int z, int w) {
	int j;
	for (j = 1; j < i; j++)
		if (heap[j].key == z) {
			heap[j].distance = w;
			break;
		}
	upHeap(heap, j);
}

void freeGraph() {
	I *node, *next;
	int i;
	for (i = 1; i <= graph.n; i++) {
		node = graph.vertex[i].head;
		while (node != NULL) {
			next = node->next;
			free(node);
			node = next;
		}
	}
	free(graph.vertex);
	free(graph.edge);
}

/*
[ 문제 2 ] (Kruskal 알고리즘) 입력으로 주어지는 그래프를 Kruskal 알고리즘을 이용하여 최소신장트리(Minimum Spanning Tree, MST)를 생성하는 프로그램을 작성하고, 최소신장트리의 생성 과정과 총무게를 결과로 출력하시오.
입력 그래프의 성질:
◦ 문제 1의 입력 그래프의 성질과 동일하다. 
구현 조건:
◦ Kruskal 알고리즘 구현 시, 우선순위 큐와 분리집합의 구현이 필요할 수 있다. 우선순위 큐는 교재의 5장, 분리집합은 4.6절을 참조하면 된다.
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct incidence {
	int edge;
	struct incidence *next;
}I;

typedef struct edge {
	int vertex1, vertex2, weight;
}E;

typedef struct vertex {
	int elem, distance;
	I *head;
}V;

typedef struct sack {
	int size;
	I *head;
}S;

typedef struct graph {
	E *edge;
	V *vertex;
	int n, m;
}G;

typedef struct heap {
	int key, distance;
}H;

G graph;

void initGraph(int n, int m);
void buildGraph();
void insertIncidentEdge(int v1, int v2, int w, int i);
void kruskalMST();
S *buildSack();
H *buildHeap();
int findSack(S *sack, int v);
void unionSack(S *s, int v1, int v2);
void downHeap(H *heap, int i, int size);
int removeMin(H *heap, int i);
void swap(H *x, H *y);
void addFirst(I **head, int i);
int deleteFirst(I **head);
void freeSack(S *sack);
void freeGraph();

int main() {

	buildGraph();
	kruskalMST();
	freeGraph();

	return 0;
}

void buildGraph() {
	int i, n, m, v1, v2, w;
	scanf("%d %d", &n, &m);
	initGraph(n, m);
	for (i = 0; i < graph.m; i++) {
		scanf("%d %d %d", &v1, &v2, &w);
		insertIncidentEdge(v1, v2, w, i);
	}
}

void initGraph(int n, int m) {
	int i;
	graph.n = n;
	graph.m = m;
	graph.vertex = (V*)malloc(sizeof(V)*(n + 1));
	graph.edge = (E*)malloc(sizeof(E)*m);
	for (i = 1; i <= n; i++)
		graph.vertex[i].elem = i;
}

void insertIncidentEdge(int v1, int v2, int w, int i) {
	graph.edge[i].vertex1 = v1;
	graph.edge[i].vertex2 = v2;
	graph.edge[i].weight = w;
}

void kruskalMST() {
	S *s = buildSack();
	H *heap = buildHeap();
	int sum = 0, u, v1, v2, size = graph.m;
	while (size > 0) {
		u = removeMin(heap, size);
		v1 = findSack(s, graph.edge[u - 1].vertex1);
		v2 = findSack(s, graph.edge[u - 1].vertex2);
		if (v1 != v2) {
			printf(" %d", graph.edge[u - 1].weight);
			sum += graph.edge[u - 1].weight;
			unionSack(s, v1, v2);
		}
		size--;
	}
	printf("\n%d", sum);
	freeSack(s);
	free(heap);
}

S *buildSack() {
	int i;
	S *s = (S*)malloc(sizeof(S)*graph.n);
	for (i = 0; i < graph.n; i++) {
		s[i].size = 0;
		s[i].head = (I*)malloc(sizeof(I));
		s[i].head->edge = graph.vertex[i + 1].elem;
		s[i].head->next = NULL;
	}
	return s;
}

H *buildHeap() {
	H *heap = (H*)malloc(sizeof(H)*(graph.m + 1));
	int i;
	for (i = 1; i <= graph.m; i++) {
		heap[i].distance = graph.edge[i - 1].weight;
		heap[i].key = i;
	}
	for (i = graph.m / 2; i >= 1; i--)
		downHeap(heap, i, graph.m);
	return heap;
}

int findSack(S *sack, int v) {
	I *p;
	int i;
	for (i = 0; i < graph.n; i++) {
		p = sack[i].head;
		while (p != NULL) {
			if (graph.vertex[p->edge].elem == v)
				return i;
			p = p->next;
		}
	}
	return -1;
}

void unionSack(S *sack, int v1, int v2) {
	int tmp, i;
	if (sack[v1].size < sack[v2].size) {
		tmp = v1;
		v1 = v2;
		v2 = tmp;
	}
	while (1) {
		i = deleteFirst(&(sack[v2].head));
		if (i == -1)
			break;
		addFirst(&(sack[v1].head), i);
	}
	sack[v2].head = NULL;
	sack[v2].size = 0;
}

void downHeap(H *heap, int i, int size) {
	int left = 2 * i, right = 2 * i + 1, smaller;
	if (left > size)
		return;
	smaller = left;
	if (right <= size)
		if (heap[right].distance < heap[left].distance)
			smaller = right;
	if (heap[i].distance <= heap[smaller].distance)
		return;
	swap(heap + i, heap + smaller);
	downHeap(heap, smaller, size);
}

void swap(H *x, H *y) {
	H tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
}

int removeMin(H *heap, int i) {
	H res = heap[1];
	if (i == 0)
		return -1;
	swap(heap + 1, heap + i);
	downHeap(heap, 1, --i);
	return res.key;
}

void addFirst(I **head, int i) {
	I *node = (I*)malloc(sizeof(I));
	node->edge = i;
	node->next = *head;
	*head = node;
}

int deleteFirst(I** head) {
	int remove;
	if (*head == NULL)
		return -1;
	remove = (*head)->edge;
	*head = (*head)->next;
	return remove;
}

void freeSack(S *sack) {
	I *p, *next;
	int i;
	for (i = 0; i < graph.n; i++) {
		p = sack[i].head;
		while (p != NULL) {
			next = p->next;
			free(p);
			p = next;
		}
	}
	free(sack);
}

void freeGraph() {
	free(graph.vertex);
	free(graph.edge);
}