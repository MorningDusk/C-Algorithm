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
	int name, distance;
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

void buildGraph();
void initGraph(int n, int m);
void insertVertex(int i);
void insertIncidenceEdge(int vertex1, int vertex2, int weight, int i);
void addFirst(I *head, int i);
void primJarnikMST();

H *buildHeap();
void upHeap(H *heap, int i);
void downHeap(H *heap, int i, int size);
void swap(H *a, H *b);
int removeMin(H *heap, int i);
int opposite(int u, int e);
int isInclude(H *heap, int i, int z);
void replaceKey(H *heap, int i, int z, int w);
void freeGraph();

int main() {

	buildGraph();
	primJarnikMST();
	freeGraph();

	return 0;
}

void buildGraph() {
	int n, m, vertex1, vertex2, weight, i;
	printf("Number of vertices: ");
	scanf("%d", &n);
	printf("Number of edges: ");
	scanf("%d", &m);
	initGraph(n, m);
	for (i = 0; i < graph.m; i++) {
		printf("Enter vertex1: ");
		scanf("%d", &vertex1);
		printf("Enter vertex2: ");
		scanf("%d", &vertex2);
		printf("Enter weight of edge: ");
		scanf("%d", &weight);
		insertIncidenceEdge(vertex1, vertex2, weight, i);
		printf("%d ------%d------ %d\n", vertex1, weight, vertex2);
	}
}

void initGraph(int n, int m) {
	int i;
	graph.n = n;
	graph.m = m;
	graph.vertex = (V*)malloc(sizeof(V)*(n+1));
	graph.edge = (E*)malloc(sizeof(E)*m);
	for (i = 1; i <= n; i++)
		insertVertex(i);
}

void insertVertex(int i) {
	graph.vertex[i].name = i;
	graph.vertex[i].head = (I*)malloc(sizeof(I));
	graph.vertex[i].head->next = NULL;
}

void insertIncidenceEdge(int vertex1, int vertex2, int weight, int i) {
	graph.edge[i].vertex1 = vertex1;
	graph.edge[i].vertex2 = vertex2;
	graph.edge[i].weight = weight;
	addFirst(graph.vertex[vertex1].head, i);
	addFirst(graph.vertex[vertex2].head, i);
}

void addFirst(I *head, int i) {
	I *node = (I*)malloc(sizeof(I));
	node->edge = i;
	node->next = head->next;
	head->next = node;
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
	printf("Vertices inside MST: ");
	while (i > 0) {
		u = removeMin(heap, i);
		printf("%d ", graph.vertex[u].name);
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
	printf("\nMST total weight: %d", sum);
	free(heap);
}

H *buildHeap() {
	H *heap = (H*)malloc(sizeof(H)*(graph.n + 1));
	int i;
	for (i = 1; i <= graph.n; i++) {
		heap[i].distance = graph.vertex[i].distance;
		heap[i].key = graph.vertex[i].name;
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

void swap(H *a, H *b) {
	H tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
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
5 
7
1
2
1
1
4
2
1
5
4
2
5
7
4
5
3
3
5
5
2
3
6
*/