/*
[ 문제 1 ] (이진탐색트리 구현) 주어진 조건을 만족하는 이진탐색트리를 구현하는 프로그램을 작성하라. 
※ 조건: 종료(q) 명령 때까지 삽입(i), 탐색(s), 삭제(d), 인쇄(p), 명령을 반복 입력받아 수행한다.
i <키> : 입력 <키>에 대한 노드 생성 및 트리에 삽입
d <키> : 입력 <키>가 트리에 존재하면 해당 노드 삭제 후 삭제된 키를 출력, 없으면 ‘X’를 출력
s <키> : 입력 <키>가 트리에 존재하면 해당 키를 출력, 없으면 ‘X’를 출력
p : 현재 트리를 전위순회로 인쇄
q : 프로그램 종료
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	struct node *parent, *lchild, *rchild;
	int key;
}NODE;

int isExternal(NODE *w) {
	if (w->lchild == NULL && w->rchild == NULL)
		return 1;
	else
		return 0;
}

int isInternal(NODE *w) {
	if (w->lchild != NULL && w->rchild != NULL)
		return 1;
	else
		return 0;
}

NODE* sibling(NODE *w) {
	if (w->parent == NULL)
		return NULL;
	if (w->parent->lchild == w)
		return w->parent->rchild;
	else
		return w->parent->lchild;
}

NODE* inOrderSucc(NODE *w) {
	w = w->rchild;
	if (isExternal(w) == 1)
		return NULL;
	while (isInternal(w->lchild) == 1)
		w = w->lchild;
	return w;
}

NODE* treeSearch(NODE* T, int key) {
	if (isExternal(T))
		return T;
	if (T->key == key)
		return T;
	else if (T->key > key)
		return treeSearch(T->lchild, key);
	else
		return treeSearch(T->rchild, key);
}

int findElement(NODE *T, int key) {
	NODE *w = treeSearch(T, key);
	if (isExternal(w) == 1)
		return 0;
	else
		return w->key;
}

void insertItem(NODE *T, int key) {
	NODE *w = treeSearch(T, key);
	NODE *lchildnode = (NODE*)malloc(sizeof(NODE));
	NODE *rchildnode = (NODE*)malloc(sizeof(NODE));
	if (isInternal(w) == 1)
		return;
	w->key = key;
	w->lchild = lchildnode;
	w->rchild = rchildnode;
	lchildnode->parent = w;
	rchildnode->parent = w;
	lchildnode->lchild = NULL;
	lchildnode->rchild = NULL;
	rchildnode->lchild = NULL;
	rchildnode->rchild = NULL;
}

NODE* reduceExternal(NODE **root, NODE *z) {
	NODE *w = z->parent;
	NODE *zs = sibling(z);
	NODE *g;
	if (w->parent == NULL) {
		(*root) = zs;
		zs->parent = NULL;
	}
	else {
		g = w->parent;
		zs->parent = g;
		if (w == g->lchild)
			g->lchild = zs;
		else if (w == g->rchild)
			g->rchild = zs;
	}
	free(z);
	free(w);
	return zs;
}

int removeElement(NODE **T, int key) {
	int e;
	NODE *w = treeSearch(*T, key), *y, *z;
	if (isExternal(w) == 1)
		return 0;
	e = w->key;
	z = w->lchild;
	if (isExternal(z) == 0)
		z = w->rchild;
	if (isExternal(z) == 1)
		w = reduceExternal(T, z);
	else {
		y = inOrderSucc(w);
		z = y->lchild;
		w->key = y->key;
		w = reduceExternal(T, z);
	}
	return e;
}

void printTree(NODE* T) {
	if (isExternal(T) == 1)
		return;
	else {
		printf(" %d", T->key);
		printTree(T->lchild);
		printTree(T->rchild);
	}
}

void freeTree(NODE *T) {
	if (isExternal(T) == 1)
		return;
	else {
		freeTree(T->lchild);
		freeTree(T->rchild);
		free(T);
	}
}

int main() {

	int key, value;
	char cmd;
	NODE *w = (NODE*)malloc(sizeof(NODE));
	w->lchild = NULL;
	w->parent = NULL;
	w->rchild = NULL;
	while (1) {
		scanf("%c", &cmd);
		if (cmd == 'i') {
			scanf("%d", &key);
			insertItem(w, key);
			getchar();
		}
		else if (cmd == 'd') {
			scanf("%d", &key);
			value = removeElement(&w, key);
			if (value == 0)
				printf("X\n");
			else
				printf("%d\n", value);
			getchar();
		}
		else if (cmd == 's') {
			scanf("%d", &key);
			if (treeSearch(w, key)->key != key)
				printf("X\n");
			else
				printf("%d\n", treeSearch(w, key)->key);
			getchar();
		}
		else if (cmd == 'p') {
			printTree(w);
			printf("\n");
		}
		else if (cmd == 'q')
			break;
	}
	freeTree(w);

	return 0;
}

/*
[ 문제 2 ] (AVL 트리 생성) 주어진 조건을 만족하는 AVL 트리를 구현하는 프로그램을 작성하라. 
1) 기본적인 입출력 구조는 문제 1과 동일하나 삭제를 제외한 삽입, 탐색, 출력을 구현한다.
2) main 함수에서 명령과 <키>를 입력받는다. 
3) 명령에 따라 AVL 트리를 생성, 탐색한다.
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	struct node *parent, *lchild, *rchild;
	int key, height;
}NODE;

int isExternal(NODE *w) {
	if (w->lchild == NULL && w->rchild == NULL)
		return 1;
	else
		return 0;
}

int isInternal(NODE *w) {
	if (w->lchild != NULL && w->rchild != NULL)
		return 1;
	else
		return 0;
}

NODE* sibling(NODE *w) {
	if (w->parent == NULL)
		return NULL;
	if (w->parent->lchild == w)
		return w->parent->rchild;
	else
		return w->parent->lchild;
}

NODE* inOrderSucc(NODE *w) {
	w = w->rchild;
	if (isExternal(w) == 1)
		return NULL;
	while (isInternal(w->lchild) == 1)
		w = w->lchild;
	return w;
}

NODE* treeSearch(NODE* T, int key) {
	if (isExternal(T))
		return T;
	if (T->key == key)
		return T;
	else if (T->key > key)
		return treeSearch(T->lchild, key);
	else
		return treeSearch(T->rchild, key);
}

void expandExternal(NODE *w) {
	NODE *lchildnode = (NODE*)malloc(sizeof(NODE));
	NODE *rchildnode = (NODE*)malloc(sizeof(NODE));
	lchildnode->lchild = NULL;
	lchildnode->rchild = NULL;
	lchildnode->height = 0;
	lchildnode->parent = w;
	rchildnode->lchild = NULL;
	rchildnode->rchild = NULL;
	rchildnode->height = 0;
	rchildnode->parent = w;
	w->lchild = lchildnode;
	w->rchild = rchildnode;
	w->height = 1;
}

int updateHeight(NODE *w) {
	int h;
	if (w->lchild->height > w->rchild->height)
		h = w->lchild->height + 1;
	else
		h = w->rchild->height + 1;
	if (h != w->height) {
		w->height = h;
		return 1;
	}
	else
		return 0;
}

int isBalanced(NODE *w) {
	if (-2 < (w->lchild->height - w->rchild->height) && (w->lchild->height - w->rchild->height) < 2)
		return 1;
	else
		return 0;
}

NODE *restructure(NODE *x, NODE *y, NODE *z, NODE **root) {
	NODE *a, *b, *c, *T1, *T2, *T3, *T0;
	if ((z->key < y->key) && (y->key < x->key)) {
		a = z;
		b = y;
		c = x;
		T0 = a->lchild;
		T1 = b->lchild;
		T2 = c->lchild;
		T3 = c->rchild;
	}
	else if ((x->key < y->key) && (y->key < z->key)) {
		a = x;
		b = y;
		c = z;
		T0 = a->lchild;
		T1 = a->rchild;
		T2 = b->rchild;
		T3 = c->rchild;
	}
	else if ((z->key < x->key) && (x->key < y->key)) {
		a = z;
		b = x;
		c = y;
		T0 = a->lchild;
		T1 = b->lchild;
		T2 = b->rchild;
		T3 = c->rchild;
	}
	else {
		a = y;
		b = x;
		c = z;
		T0 = a->lchild;
		T1 = b->lchild;
		T2 = b->rchild;
		T3 = c->rchild;
	}

	if (z->parent == NULL) {
		*root = b;
		b->parent = NULL;
	}
	else if (z->parent->lchild == z) {
		z->parent->lchild = b;
		b->parent = z->parent;
	}
	else if (z->parent->rchild == z) {
		z->parent->rchild = b;
		b->parent = z->parent;
	}

	a->lchild = T0;
	a->rchild = T1;
	T0->parent = a;
	T1->parent = a;
	updateHeight(a);

	c->lchild = T2;
	c->rchild = T3;
	T2->parent = c;
	T3->parent = c;
	updateHeight(c);

	b->lchild = a;
	b->rchild = c;
	a->parent = b;
	c->parent = b;
	updateHeight(b);

	return b;
}

void searchAndFixAfterInsertion(NODE* w, NODE **root) {
	NODE *x, *y, *z;
	w->lchild->height = 0;
	w->rchild->height = 0;
	w->height = 1;
	if (w->parent == NULL)
		return;
	z = w->parent;
	while (updateHeight(z) == 1 && isBalanced(z) == 1) {
		if (z->parent == NULL)
			return;
		z = z->parent;
	}
	if (isBalanced(z) == 1)
		return;

	if (z->lchild->height > z->rchild->height)
		y = z->lchild;
	else
		y = z->rchild;
	if (y->lchild->height > y->rchild->height)
		x = y->lchild;
	else
		x = y->rchild;
	restructure(x, y, z, root);
}

void insertItem(NODE **T, int key) {
	NODE *w = treeSearch(*T, key);
	if (isInternal(w) == 1)
		return;
	else {
		w->key = key;
		expandExternal(w);
		searchAndFixAfterInsertion(w, T);
	}
}

NODE* reduceExternal(NODE **root, NODE *z) {
	NODE *w = z->parent;
	NODE *zs = sibling(z);
	NODE *g;
	if (w->parent == NULL) {
		(*root) = zs;
		zs->parent = NULL;
	}
	else {
		g = w->parent;
		zs->parent = g;
		if (w == g->lchild)
			g->lchild = zs;
		else if (w == g->rchild)
			g->rchild = zs;
	}
	free(z);
	free(w);
	return zs;
}

void searchAndFixAfterRemoval(NODE *w, NODE **root) {
	NODE *x, *y, *z, *b;
	if (w == NULL)
		return;
	z = w;
	while (updateHeight(z) && isBalanced(z)) {
		if (z->parent == NULL)
			return;
		z = z->parent;
	}
	if (isBalanced(z))
		return;

	if (z->lchild->height > z->rchild->height)
		y = z->lchild;
	else
		y = z->rchild;

	if (y->lchild->height > y->rchild->height)
		x = y->lchild;
	else if (y->lchild->height < y->rchild->height)
		x = y->rchild;
	else {
		if (z->lchild == y)
			x = y->lchild;
		else if (z->rchild == y)
			x = y->rchild;
	}
	b = restructure(x, y, z, root);
	if (b->parent == NULL)
		return;
	searchAndFixAfterRemoval(b->parent, root);
}

int removeElement(NODE **T, int key) {
	int e;
	NODE *w = treeSearch(*T, key), *y, *z;
	if (isExternal(w) == 1)
		return 0;
	e = w->key;
	z = w->lchild;
	if (isExternal(z) == 0)
		z = w->rchild;
	if (isExternal(z) == 1)
		w = reduceExternal(T, z);
	else {
		y = inOrderSucc(w);
		z = y->lchild;
		w->key = y->key;
		w = reduceExternal(T, z);
	}
	return e;
}

void printTree(NODE* T) {
	if (isExternal(T) == 1)
		return;
	else {
		printf(" %d", T->key);
		printTree(T->lchild);
		printTree(T->rchild);
	}
}

void freeTree(NODE *T) {
	if (isExternal(T) == 1)
		return;
	else {
		freeTree(T->lchild);
		freeTree(T->rchild);
		free(T);
	}
}

int main() {

	int key, value;
	char cmd;

	NODE *root = (NODE*)malloc(sizeof(NODE));

	root->lchild = root->rchild = NULL; root->key = -1; root->height = 0;
	while (1) {
		scanf("%c", &cmd);
		if (cmd == 'i') {
			scanf("%d", &key);
			insertItem(&root, key);
			getchar();
		}
		else if (cmd == 'd') {
			scanf("%d", &key);
			value = removeElement(&root, key);
			if (value == 0)
				printf("X\n");
			else
				printf("%d\n", value);
			getchar();
		}
		else if (cmd == 's') {
			scanf("%d", &key);
			if (treeSearch(root, key)->key != key)
				printf("X\n");
			else
				printf("%d\n", treeSearch(root, key)->key);
			getchar();
		}
		else if (cmd == 'p') {
			printTree(root);
			printf("\n");
		}
		else if (cmd == 'q')
			break;
	}
	freeTree(root);

	return 0;
}

/*
[ 문제 3 ] (AVL 트리 삭제) AVL 트리에서 삭제를 구현하라.
 1) 기본적인 입출력 구조는 문제 2와 동일하며 삭제를 추가하여 구현한다. 
 2) main 함수에서 명령과 <키>를 입력받는다. 
 3) 명령에 따라 AVL 트리를 생성한다
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	struct node *parent, *lchild, *rchild;
	int key, height;
}NODE;

int isExternal(NODE *w) {
	if (w->lchild == NULL && w->rchild == NULL)
		return 1;
	else
		return 0;
}

int isInternal(NODE *w) {
	if (w->lchild != NULL && w->rchild != NULL)
		return 1;
	else
		return 0;
}

NODE* sibling(NODE *w) {
	if (w->parent == NULL)
		return NULL;
	if (w->parent->lchild == w)
		return w->parent->rchild;
	else
		return w->parent->lchild;
}

NODE* inOrderSucc(NODE *w) {
	w = w->rchild;
	if (isExternal(w) == 1)
		return NULL;
	while (isInternal(w->lchild) == 1)
		w = w->lchild;
	return w;
}

NODE* treeSearch(NODE* T, int key) {
	if (isExternal(T))
		return T;
	if (T->key == key)
		return T;
	else if (T->key > key)
		return treeSearch(T->lchild, key);
	else
		return treeSearch(T->rchild, key);
}

void expandExternal(NODE *w) {
	NODE *lchildnode = (NODE*)malloc(sizeof(NODE));
	NODE *rchildnode = (NODE*)malloc(sizeof(NODE));
	lchildnode->lchild = NULL;
	lchildnode->rchild = NULL;
	lchildnode->height = 0;
	lchildnode->parent = w;
	rchildnode->lchild = NULL;
	rchildnode->rchild = NULL;
	rchildnode->height = 0;
	rchildnode->parent = w;
	w->lchild = lchildnode;
	w->rchild = rchildnode;
	w->height = 1;
}

int updateHeight(NODE *w) {
	int h;
	if (w->lchild->height > w->rchild->height)
		h = w->lchild->height + 1;
	else
		h = w->rchild->height + 1;
	if (h != w->height) {
		w->height = h;
		return 1;
	}
	else
		return 0;
}

int isBalanced(NODE *w) {
	if (-2 < (w->lchild->height - w->rchild->height) && (w->lchild->height - w->rchild->height) < 2)
		return 1;
	else
		return 0;
}

NODE *restructure(NODE *x, NODE *y, NODE *z, NODE **root) {
	NODE *a, *b, *c, *T1, *T2, *T3, *T0;
	if ((z->key < y->key) && (y->key < x->key)) {
		a = z;
		b = y;
		c = x;
		T0 = a->lchild;
		T1 = b->lchild;
		T2 = c->lchild;
		T3 = c->rchild;
	}
	else if ((x->key < y->key) && (y->key < z->key)) {
		a = x;
		b = y;
		c = z;
		T0 = a->lchild;
		T1 = a->rchild;
		T2 = b->rchild;
		T3 = c->rchild;
	}
	else if ((z->key < x->key) && (x->key < y->key)) {
		a = z;
		b = x;
		c = y;
		T0 = a->lchild;
		T1 = b->lchild;
		T2 = b->rchild;
		T3 = c->rchild;
	}
	else {
		a = y;
		b = x;
		c = z;
		T0 = a->lchild;
		T1 = b->lchild;
		T2 = b->rchild;
		T3 = c->rchild;
	}

	if (z->parent == NULL) {
		*root = b;
		b->parent = NULL;
	}
	else if (z->parent->lchild == z) {
		z->parent->lchild = b;
		b->parent = z->parent;
	}
	else if (z->parent->rchild == z) {
		z->parent->rchild = b;
		b->parent = z->parent;
	}

	a->lchild = T0;
	a->rchild = T1;
	T0->parent = a;
	T1->parent = a;
	updateHeight(a);

	c->lchild = T2;
	c->rchild = T3;
	T2->parent = c;
	T3->parent = c;
	updateHeight(c);

	b->lchild = a;
	b->rchild = c;
	a->parent = b;
	c->parent = b;
	updateHeight(b);

	return b;
}

void searchAndFixAfterInsertion(NODE* w, NODE **root) {
	NODE *x, *y, *z;
	w->lchild->height = 0;
	w->rchild->height = 0;
	w->height = 1;
	if (w->parent == NULL)
		return;
	z = w->parent;
	while (updateHeight(z) == 1 && isBalanced(z) == 1) {
		if (z->parent == NULL)
			return;
		z = z->parent;
	}
	if (isBalanced(z) == 1)
		return;

	if (z->lchild->height > z->rchild->height)
		y = z->lchild;
	else
		y = z->rchild;
	if (y->lchild->height > y->rchild->height)
		x = y->lchild;
	else
		x = y->rchild;
	restructure(x, y, z, root);
}

void insertItem(NODE **T, int key) {
	NODE *w = treeSearch(*T, key);
	if (isInternal(w) == 1)
		return;
	else {
		w->key = key;
		expandExternal(w);
		searchAndFixAfterInsertion(w, T);
	}
}

NODE* reduceExternal(NODE **root, NODE *z) {
	NODE *w = z->parent;
	NODE *zs = sibling(z);
	NODE *g;
	if (w->parent == NULL) {
		(*root) = zs;
		zs->parent = NULL;
	}
	else {
		g = w->parent;
		zs->parent = g;
		if (w == g->lchild)
			g->lchild = zs;
		else if (w == g->rchild)
			g->rchild = zs;
	}
	free(z);
	free(w);
	return zs;
}

void searchAndFixAfterRemoval(NODE *w, NODE **root) {
	NODE *x, *y, *z, *b;
	if (w == NULL)
		return;
	z = w;
	while (updateHeight(z) && isBalanced(z)) {
		if (z->parent == NULL)
			return;
		z = z->parent;
	}
	if (isBalanced(z))
		return;

	if (z->lchild->height > z->rchild->height)
		y = z->lchild;
	else
		y = z->rchild;

	if (y->lchild->height > y->rchild->height)
		x = y->lchild;
	else if (y->lchild->height < y->rchild->height)
		x = y->rchild;
	else {
		if (z->lchild == y)
			x = y->lchild;
		else if (z->rchild == y)
			x = y->rchild;
	}
	b = restructure(x, y, z, root);
	if (b->parent == NULL)
		return;
	searchAndFixAfterRemoval(b->parent, root);
}

int removeElement(NODE **T, int key) {
	int e;
	NODE *w = treeSearch(*T, key), *y, *z, *zs;
	if (isExternal(w) == 1)
		return 0;
	e = w->key;
	z = w->lchild;
	if (isExternal(z) == 0)
		z = w->rchild;
	if (isExternal(z) == 1)
		zs = reduceExternal(T, z);
	else {
		y = inOrderSucc(w);
		z = y->lchild;
		w->key = y->key;
		zs = reduceExternal(T, z);
	}
	searchAndFixAfterRemoval(zs->parent, T);
	return e;
}

void printTree(NODE* T) {
	if (isExternal(T) == 1)
		return;
	else {
		printf(" %d", T->key);
		printTree(T->lchild);
		printTree(T->rchild);
	}
}

void freeTree(NODE *T) {
	if (isExternal(T) == 1)
		return;
	else {
		freeTree(T->lchild);
		freeTree(T->rchild);
		free(T);
	}
}

int main() {

	int key, value;
	char cmd;

	NODE *root = (NODE*)malloc(sizeof(NODE));

	root->lchild = root->rchild = NULL; root->key = -1; root->height = 0;
	while (1) {
		scanf("%c", &cmd);
		if (cmd == 'i') {
			scanf("%d", &key);
			insertItem(&root, key);
			getchar();
		}
		else if (cmd == 'd') {
			scanf("%d", &key);
			value = removeElement(&root, key);
			if (value == 0)
				printf("X\n");
			else
				printf("%d\n", value);
			getchar();
		}
		else if (cmd == 's') {
			scanf("%d", &key);
			if (treeSearch(root, key)->key != key)
				printf("X\n");
			else
				printf("%d\n", treeSearch(root, key)->key);
			getchar();
		}
		else if (cmd == 'p') {
			printTree(root);
			printf("\n");
		}
		else if (cmd == 'q')
			break;
	}
	freeTree(root);

	return 0;
}

/*
[문제 3] 양의 정수N과 N개의 (학생ID, 학생이름) 정보가 입력이 된다. 
(학생ID의 오름차순으로 정렬된 순서로 입력이 됨)
찾고자 하는 학생ID를 입력받아 그 학생의 이름을 출력하는 코드를 이진탐색법으로 작성하여라. 
학생ID는 중복이 없다. 
학생ID: 정수 
학생이름 : 최대 20자리 문자
N <= 100, 이진 탐색법을 사용하지 않으면 0점. 만일 찾는 학생ID가 없는 경우에는 -1을 출력
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct student {
	char stuName[21];
	int stuID;
}STUDENT;

int findElement(STUDENT *st, int id, int l, int r) {
	if (l == r) {
		if ((st + l)->stuID == id)
			return l;
		else
			return -1;
	}
	int mid = (l + r) / 2;
	int a = findElement(st, id, l, mid);
	int b = findElement(st, id, mid + 1, r);
	if (a >= b)
		return a;
	else
		return b;
}

int main() {

	int id, n, i, element;
	STUDENT *st;
	scanf("%d", &n);
	getchar();
	st = (STUDENT*)malloc(sizeof(STUDENT)*n);
	for (i = 0; i < n; i++)
		scanf("%d %s", &(st + i)->stuID, (st + i)->stuName);

	scanf("%d", &id);
	element = findElement(st, id, 0, n - 1);
	if (element == -1)
		printf("-1");
	else
		printf("%d %s", (st + element)->stuID, (st + element)->stuName);

	free(st);

	return 0;
}

