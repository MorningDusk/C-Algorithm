/*
[ 문제 1 ] (인접리스트 구현) 그림 1의 무방향 가중그래프를 인접리스트로 표현하고, 다음
명령어에 따라 그래프 정보를 출력하거나 그래프를 수정하는 프로그램을 작성하시오. 대화식 프로그램에 주어지는 명령어는 a, m, q 세 가지며 각 명령에 대해 다음과 같이
수행해야 한다. 
a <node number> : <node number>를 가지는 node와 인접한 node와 그 노드까지의 간선 가중치를 모두 인쇄. 
단, node number의 오름차순으로 인쇄하되, space 외의 구분자 없이 노드번호 가중치 노드번호 가중치 ... 형식으로 인쇄한다. 
그래프에 정점 a가 존재하지 않으면 아무 것도 하지 않고 –1을 출력한다.
m a b w : 간선 (a, b)의 가중치를 w로 변경한다. 그러한 간선이 존재하지 않을 때는 가중치 w인 새로운 간선 (a, b)를 생성한다. 
w = 0이면 간선 (a, b)를 삭제한다. 
그래프에 정점 a 혹은 b가 존재하지 않으면 아무 것도 하지 않고 –1을 출력한다. 
q : 프로그램 종료
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct incidence {
	int edge;
	struct incidence *next;
}IE;

typedef struct vertex {
	int elem;
	IE *incidence;
}V;

typedef struct edge {
	int v1, v2, weight;
}E;

typedef struct graph {
	V vertices[7];
	E edges[21];
	int edgesize;
}G;

IE* getIncidence(int edge) {
	IE *node = (IE*)malloc(sizeof(IE));
	node->next = NULL;
	node->edge = edge;
	return node;
}

void insertIncidence(int v1, int v2, IE *incidence, G *graph) {
	E *edge = graph->edges;
	V *vertices = graph->vertices;
	IE *p;
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

void deleteIncidence(int v1, int v2, G *graph) {
	E *edge = graph->edges;
	V *vertices = graph->vertices;
	IE *p;
	int tmp;
	p = vertices[v1].incidence;
	if (p == NULL)
		return;
	if (edge[p->edge].v1 == v1)
		tmp = edge[p->edge].v2;
	else
		tmp = edge[p->edge].v1;
	if (tmp == v2) {
		vertices[v1].incidence = p->next;
		free(p);
	}
	else {
		while (p->next != NULL) {
			if (edge[p->next->edge].v1 == v1)
				tmp = edge[p->next->edge].v2;
			else
				tmp = edge[p->next->edge].v1;
			if (tmp == v2)
				break;
			p = p->next;
		}
		if (p->next == NULL)
			return;
		else
			p->next = p->next->next;
	}
}

void insertEdge(int v1, int v2, int w, G *graph) {
	E *edge = graph->edges;
	IE *i1, *i2;
	int i, j = -1;
	for (i = 0; i < graph->edgesize; i++) {
		if (edge[i].v1 == v1 && edge[i].v2 == v2) {
			edge[i].weight = w;
			j = i;
			break;
		}
		if (edge[i].v1 == v2 && edge[i].v2 == v1) {
			edge[i].weight = w;
			j = i;
			break;
		}
	}
	if (j == -1)
		j = graph->edgesize;
	edge[j].v1 = v1;
	edge[j].v2 = v2;
	edge[j].weight = w;
	i1 = getIncidence(j);
	i2 = getIncidence(j);
	insertIncidence(v1, v2, i1, graph);
	if (v1 != v2)
		insertIncidence(v2, v1, i2, graph);
	graph->edgesize += 1;
}

void deleteEdge(int v1, int v2, G *graph) {
	E *edge = graph->edges;
	V *vertices = graph->vertices;
	if (v1 < 1 || v1>6 || v2 < 1 || v2>6) {
		printf("-1\n");
		return;
	}
	deleteIncidence(v1, v2, graph);
	if (v1 != v2)
		deleteIncidence(v2, v1, graph);
	graph->edgesize -= 1;
}

void modify(int v1, int v2, int w, G *graph) {
	E *edge = graph->edges;
	IE *p = graph->vertices[v1].incidence;
	int tmp, flag = 0;
	if (v1 < 1 || v1>6 || v2 < 1 || v2>6) {
		printf("-1\n");
		return;
	}
	if (p == NULL)
		insertEdge(v1, v2, w, graph);
	else {
		while (p != NULL) {
			if (edge[p->edge].v1 == v1)
				tmp = edge[p->edge].v2;
			else
				tmp = edge[p->edge].v1;
			if (tmp == v2) {
				edge[p->edge].weight = w;
				flag = 1;
				break;
			}
			p = p->next;
		}
		if (flag == 0)
			insertEdge(v1, v2, w, graph);
	}
}

void initGraph(G *graph) {
	int i;
	graph->edgesize = 0;
	for (i = 1; i <= 6; i++) {
		graph->vertices[i].incidence = NULL;
		graph->vertices[i].elem = i;
	}
	insertEdge(1, 2, 1, graph);
	insertEdge(1, 3, 1, graph);
	insertEdge(1, 4, 1, graph);
	insertEdge(1, 6, 2, graph);
	insertEdge(2, 3, 1, graph);
	insertEdge(3, 5, 4, graph);
	insertEdge(5, 5, 4, graph);
	insertEdge(5, 6, 3, graph);
}

void printEdge(int v, G *graph) {
	V *vertices = graph->vertices;
	E *edge = graph->edges;
	IE *p = vertices[v].incidence;
	int tmp;
	if (v < 1 || v > 6) {
		printf("-1\n");
		return;
	}
	if (p == NULL)
		return;
	while (p != NULL) {
		if (edge[p->edge].v1 == v)
			tmp = edge[p->edge].v2;
		else
			tmp = edge[p->edge].v1;
		printf(" %d %d", tmp, edge[p->edge].weight);
		p = p->next;
	}
	printf("\n");
}

int main() {

	G graph;
	char cmd;
	int a, b, w;
	initGraph(&graph);
	while (1) {
		scanf("%c", &cmd);
		if (cmd == 'a') {
			scanf("%d", &a);
			printEdge(a, &graph);
		}
		else if (cmd == 'm') {
			scanf("%d %d %d", &a, &b, &w);
			if (w != 0)
				modify(a, b, w, &graph);
			else
				deleteEdge(a, b, &graph);
		}
		else if (cmd == 'q')
			break;
		getchar();
	}

	return 0;
}

/*
[ 문제 2 ] (인접행렬 구현) 그림 1의 무방향 가중그래프를 인접행렬로 표현하고, 명령어에 따라 그래프 정보를 인쇄하거나 그래프를 수정하는 프로그램을 작성하시오. 
명령어 정의와 입출력 예시는 문제 1과 같다.
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct edge {
	int v1, v2, weight;
}E;

typedef struct graph {
	int vertices[6], adjency[6][6], edgeSize;
	E edges[21];
}G;

void insertEdge(int v1, int v2, int w, G *graph) {
	E *edge = graph->edges;
	int i = 0, j = -1;
	for (i = 0; i < graph->edgeSize; i++) {
		if (edge[i].v1 == v1 && edge[i].v2 == v2) {
			edge[i].weight = w;
			j = i;
			break;
		}
		if (edge[i].v1 == v2 && edge[i].v2 == v1) {
			edge[i].weight = w;
			j = i;
			break;
		}
	}
	if (j == -1)
		j = graph->edgeSize;
	edge[j].v1 = v1;
	edge[j].v2 = v2;
	edge[j].weight = w;
	graph->adjency[v1][v2] = j;
	graph->adjency[v2][v1] = j;
	graph->edgeSize += 1;
}

void deleteEdge(int v1, int v2, G *graph) {
	E *edge = graph->edges;
	if (v1 < 0 || v1 > 5 || v2 < 0 || v2 > 5) {
		printf("-1\n");
		return;
	}
	graph->adjency[v1][v2] = -1;
	graph->adjency[v2][v1] = -1;
	graph->edgeSize -= 1;
}

void modify(int v1, int v2, int w, G *graph) {
	E *edge = graph->edges;
	if (v1 < 0 || v1 > 5 || v2 < 0 || v2 > 5) {
		printf("-1\n");
		return;
	}
	if (graph->adjency[v1][v2] == -1)
		insertEdge(v1, v2, w, graph);
	else
		edge[graph->adjency[v1][v2]].weight = w;
}

void initGraph(G *graph) {
	int i, j;
	graph->edgeSize = 0;
	for (i = 0; i < 6; i++) {
		graph->vertices[i] = i;
		for (j = 0; j < 6; j++)
			graph->adjency[i][j] = -1;
	}
	insertEdge(1 - 1, 2 - 1, 1, graph);
	insertEdge(1 - 1, 3 - 1, 1, graph);
	insertEdge(1 - 1, 4 - 1, 1, graph);
	insertEdge(1 - 1, 6 - 1, 2, graph);
	insertEdge(2 - 1, 3 - 1, 1, graph);
	insertEdge(3 - 1, 5 - 1, 4, graph);
	insertEdge(5 - 1, 5 - 1, 4, graph);
	insertEdge(5 - 1, 6 - 1, 3, graph);
}

void printEdge(int v, G *graph) {
	int i, j;
	E *edge = graph->edges;
	if (v < 0 || v > 5) {
		printf("-1\n");
		return;
	}
	for (i = 0; i < 6; i++) {
		j = graph->adjency[v][i];
		if (j == -1)
			continue;
		printf(" %d %d", i + 1, edge[j].weight);
	}
	printf("\n");
}

int main() {

	G graph;
	char cmd;
	int a, b, w;
	initGraph(&graph);
	while (1) {
		scanf("%c", &cmd);
		if (cmd == 'a') {
			scanf("%d", &a);
			printEdge(a - 1, &graph);
		}
		else if (cmd == 'm') {
			scanf("%d %d %d", &a, &b, &w);
			if (w != 0)
				modify(a - 1, b - 1, w, &graph);
			else
				deleteEdge(a - 1, b - 1, &graph);
		}
		else if (cmd == 'q')
			break;
	}

	return 0;
}