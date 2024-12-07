/*
[ 문제 1 ] 위에서 설명한 이중연결리스트를 이용하여 영문자 리스트 ADT를 구현하시오.

◦ 다음 네 가지 연산을 지원해야 함 (순위는 1부터 시작한다고 가정)
- add(list, r, e) : list의 순위 r에 원소 e를 추가한다.
- delete(list, r) : list의 순위 r에 위치한 원소를 삭제한다 (주교재의 remove와 동일)
- get(list, r) : list의 순위 r에 위치한 원소를 반환한다.
- print(list) : list의 모든 원소를 저장 순위대로 공백없이 출력한다.
※ 순위 정보가 유효하지 않으면 화면에 에러 메시지 "invalid position"을 출력하고, 해당 연산을 무시한다.

◦ 입력에 대한 설명 (아래 입출력 예시 참조)
- 각 연산의 내용이 한 줄에 한 개씩 입력되고, 한 개의 줄에는 연산의 종류, 순위, 원소 순서로 입력된다.
- 연산의 종류: 연산 이름의 맨 앞 영문자가 대문자 A, D, G, P로 주어진다.
- 순위: 양의 정수
- 원소: 영문자(대문자, 소문자 모두 가능)
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	struct node* prev;
	char elem;
	struct node* next;

}node;

typedef struct _list {
	node* head;
	int position;
	node* tail;
}list;

void init(list* lptr) {
	node *ohead, *otail;
	ohead = (node*)malloc(sizeof(node));
	otail = (node*)malloc(sizeof(node));

	lptr->head = ohead;
	ohead->prev = NULL;
	ohead->next = otail;


	lptr->tail = otail;
	otail->next = NULL;
	otail->prev = ohead;

	lptr->position = 2;
}

void add(list* lptr) {
	int tposi;
	char nwel;
	int order;
	scanf("%d %c", &order, &nwel);
	getchar();

	if ((lptr->position) - 1 < order) {
		printf("invalid position\n");
		return;
	}

	node *temp;
	temp = lptr->head;

	struct node *newnode;
	newnode = (struct node*)malloc(sizeof(struct node));
	newnode->elem = nwel;

	for (int i = 0; i < order; i++) {
		temp = temp->next;
	}
	newnode->next = temp;
	newnode->prev = temp->prev;
	temp->prev = newnode;
	temp = newnode->prev;
	temp->next = newnode;
	tposi = (lptr->position);
	tposi++;
	lptr->position = tposi;

}

void del(list* lptr) {
	int tposi;
	int order;
	scanf("%d", &order);
	getchar();

	if ((lptr->position) - 2 < order) {
		printf("invalid position\n");
		return;
	}

	node *temp, *ptemp, *ntemp;

	temp = lptr->head;

	for (int i = 0; i < order; i++) {
		temp = temp->next;
	}
	ptemp = temp->prev;
	ntemp = temp->next;
	ptemp->next = ntemp;
	ntemp->prev = ptemp;
	free(temp);
	tposi = (lptr->position);
	tposi--;
	lptr->position = tposi;
}

void get_entry(list* lptr) {
	node *temp;
	temp = lptr->head;
	int getnum;
	scanf("%d", &getnum);
	getchar();

	if ((lptr->position) - 2 < getnum) {
		printf("invalid position\n");
		return;
	}


	for (int i = 0; i < getnum; i++) {
		temp = temp->next;
	}

	printf("%c\n", temp->elem);
}

void printlist(list* lptr) {
	node *temp;
	temp = lptr->head;

	for (int i = 0; i < (lptr->position) - 2; i++) {
		temp = temp->next;
		printf("%c", temp->elem);
	}
	printf("\n");
}


int main(void) {
	int num;
	char command1;

	list* L;
	L = (list*)malloc(sizeof(list));
	init(L);

	scanf("%d", &num);
	getchar();
	for (int i = 0; i < num; i++) {
		scanf("%c", &command1);
		getchar();

		if (command1 == 'A') {
			add(L);
			continue;
		}
		else if (command1 == 'D') {
			del(L);
			continue;
		}
		else if (command1 == 'G') {
			get_entry(L);
			continue;
		}
		else if (command1 == 'P') {
			printlist(L);
			continue;
		}
	}

	return 0;
}

/*
[ 문제 1 ] 위의 설명과 같이 다항식을 헤더 단일연결리스트로 표현하고, 다항식의 덧셈을 구하는 프로그램을 작성하라.
◦ 입력에 대한 설명(아래 입출력 예시 참조)
- 첫 번째 다항식의 항의 개수가 입력되고, 이후에 다항식의 각 항의 (계수, 지수) 쌍이 지수의 내림차순으로 입력됨
- 동일한 방식으로 두 번째 다항식의 정보가 입력됨

◦ 출력에 대한 설명(아래 입출력 예시 참조)
- 결과 다항식의 각 항의 (계수, 지수) 쌍을 지수의 내림차순으로 출력

Alg appendTerm(k, c, e)
	input last term of a polynomial expression k, coefficient c, exponent e
	output cxe appended to k

1. t ← getnode()
2. t.coef ← c
3. t.exp ← e
4. t.next ← NULL
5. k.next ← t
6. k ← t				{update k to t}
7. return

Alg addPoly(x, y)
	input polynomial expression x, y
	output x + y

1. result ← getnode()				{new header}
2. result.next ← NULL  			{may be null}
3. i, j ← x.next, y.next			{skip headers}
4. k ← result
5. while ((i ≠ NULL) & (j ≠ NULL))
		if (i.exp > j.exp)
			appendTerm(k, i.coef, i.exp)
			i ← i.next
		elseif (i.exp < j.exp)
			appendTerm(k, j.coef, j.exp)
			j ← j.next
		else
			sum ← i.coef + j.coef
			if (sum ≠ 0)
				appendTerm(k, sum, i.exp)
			i, j ← i.next, j.next
6. while (i ≠ NULL)
		appendTerm(k, i.coef, i.exp)
		i ← i.next
7. while (j ≠ NULL)
		appendTerm(k, j.coef, j.exp)
		j ← j.next
8. return result
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct polynomial {
	int coef, exp;
	struct polynomial *next;
}polynomial;

polynomial* appendTerm(polynomial *k, int c, int e) {
	polynomial *t = (polynomial*)malloc(sizeof(polynomial));
	t->coef = c;
	t->exp = e;
	t->next = NULL;
	k->next = t;
	k = t;
	return k;
}

polynomial* addpolynomial(polynomial *x, polynomial *y) {
	polynomial *result = (polynomial*)malloc(sizeof(polynomial));
	result->next = NULL;
	polynomial *i = x->next, *j = y->next;
	polynomial *k = result;
	int sum;

	while (i != NULL && j != NULL) {
		if (i->exp > j->exp) {
			result = appendTerm(result, i->coef, i->exp);
			i = i->next;
		}
		else if (i->exp < j->exp) {
			result = appendTerm(result, j->coef, j->exp);
			j = j->next;
		}
		else {
			sum = i->coef + j->coef;
			if (sum != 0)
				result = appendTerm(result, sum, i->exp);
			i = i->next;
			j = j->next;
		}
	}
	while (i != NULL) {
		result = appendTerm(result, i->coef, i->exp);
		i = i->next;
	}
	while (j != NULL) {
		result = appendTerm(result, j->coef, j->exp);
		j = j->next;
	}

	return k;
}

int main() {

	int n, m, i, coef, exp;
	scanf("%d", &n);
	getchar();
	polynomial *x = (polynomial*)malloc(n * sizeof(polynomial));
	x->next = NULL;
	polynomial *xh = x;
	for (i = 0; i < n; i++) {
		scanf("%d %d", &coef, &exp);
		x = appendTerm(x, coef, exp);
	}

	scanf("%d", &m);
	getchar();
	polynomial *y = (polynomial*)malloc(m * sizeof(polynomial));
	y->next = NULL;
	polynomial *yh = y;
	for (i = 0; i < m; i++) {
		scanf("%d %d", &coef, &exp);
		y = appendTerm(y, coef, exp);
	}

	polynomial *z = addpolynomial(xh, yh);
	polynomial *zh = z;
	for (zh; zh = zh->next;) {
		printf(" %d %d", zh->coef, zh->exp);
	}

	return 0;
}