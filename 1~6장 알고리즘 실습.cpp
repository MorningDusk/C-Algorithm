//우선순위 큐

/*
[ 문제 1 ] (선택 정렬) n개의 양의 정수(중복 가능)를 입력받아, 아래에서 설명하는 선택 정렬을 이용하여 정렬하는 프로그램을 작성하시오.
◦ 구현해야 할 선택 정렬 알고리즘 (가장 큰 값을 찾는 버전): 
- 크기가 n인 배열을 동적 할당하여, 입력된 양의 정수 저장(입력 정수는 중복 가능) 
- 제자리(in place) 정렬 사용. 즉, 입력 값 저장을 위한 배열 이외에 O(1)의 추가 공간만 사용
- 배열의 뒷 부분을 정렬 상태로 유지하고, 매 반복마다 최대 한 번의 교환 연산만 사용
(매 반복마다 가장 큰 값을 찾아, 오른쪽부터 채우는 방식으로 정렬) - 가능하면 교재의 의사코드를 보지 말고 구현해볼 것을 권장
- 참고: 아래 그림에 예시된 버전은 매 반복마다 가장 작은 값을 찾아 왼쪽부터 채워 나가는, 따라서 교재의 알고리즘과는 정반대 방향으로 작동하는 버전이다.
*/

#include<stdio.h>
#include<stdlib.h>

int* inPlaceSelectionSort(int arr[], int n) {
	int i, j, minloc, tmp;
	for (i = 0; i < n - 1; i++) {
		minloc = i;
		for (j = i + 1; j < n; j++) {
			if (arr[j] < arr[minloc])
				minloc = j;
		}
		tmp = arr[i];
		arr[i] = arr[minloc];
		arr[minloc] = tmp;
	}
	return arr;
}

int main() {

	int i, n, *arr = NULL;
	scanf("%d", &n);
	getchar();
	arr = (int*)malloc(sizeof(int)*n);
	for (i = 0; i < n; i++)
		scanf("%d", &arr[i]);

	arr = inPlaceSelectionSort(arr, n);

	for (i = 0; i < n; i++)
		printf(" %d", arr[i]);

	free(arr);

	return 0;
}

/*
[ 문제 2 ] (삽입 정렬) n개의 양의 정수를 입력(중복 가능)받아, 아래에서 설명하는 삽입 정렬을 이용하여 정렬하는 프로그램을 작성하시오. 
◦ 구현해야 할 삽입 정렬 알고리즘:
- 크기가 n인 배열을 동적 할당하여, 입력된 양의 정수 저장(입력 정수는 중복 가능)
- 제자리(in-place) 정렬 사용. 즉, 입력 값 저장을 위한 배열 이외에 O(1)의 추가 공간만 사용
- 배열의 앞부분을 정렬 상태로 유지
- 가능하면 교재의 의사코드를 보지 말고 구현해볼 것을 권장
*/

#include<stdio.h>
#include<stdlib.h>

int* inPlaceInsertionSort(int arr[], int n) {
	int i, j, save;
	for (i = 1; i < n; i++) {
		save = arr[i];
		j = i - 1;
		while ((j >= 0) && (arr[j] > save)) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = save;
	}
	return arr;
}

int main() {

	int i, n, *arr = NULL;
	scanf("%d", &n);
	getchar();
	arr = (int*)malloc(sizeof(int)*n);
	for (i = 0; i < n; i++)
		scanf("%d", &arr[i]);

	arr = inPlaceInsertionSort(arr, n);

	for (i = 0; i < n; i++)
		printf(" %d", arr[i]);

	free(arr);

	return 0;
}

//힙 정렬

/*
[ 문제 1 ] 삽입식 힙 생성
다음의 대화식 프로그램을 작성해 삽입식 힙 생성을 구현하라. 
1) 키들은 한 개씩 차례로 삽입 명령과 함께 주어진다. 즉, 키가 입력될 때마다 즉시 힙에 삽입해야 한다. 
만약 이렇게 하지 않고 문제 2에서 하는 것처럼 키들이 모두 입력되기를 기다려 한꺼번에 상향식으로 힙을 생성하면 대화식 프로그램의 인쇄(p) 또는 삭제(d)명령의 수행이 어려워진다. 
2) 대화식 프로그램에 주어지는 명령은 i, d, p, q 네 가지며 각 명령에 대해 다음과 같이 수행해야 한다.
i <키> : <키>를 힙에 삽입하고 0을 인쇄.
d : 힙에서 삭제(이때 루트에 저장된 키가 삭제되어야 한다)하여 반환된 키를 인쇄. 
p : 힙의 내용을 인쇄(이때 이진트리의 레벨순서로 항목들을 인쇄해야 한다).
* 레벨순서란 이진트리의 레벨 0의 노드부터 다음 레벨 1, 2, 3, ...의
노드들을 차례로 방문한다. 같은 레벨의 노드들은 왼쪽에서 오른쪽으로
방문한다. 
q : 프로그램 종료
*/

#include<stdio.h>
#include<stdlib.h>

void insertItem(int key, int heap[], int *n);
int removeMax(int heap[], int *n);
void upHeap(int i, int heap[]);
void downHeap(int i, int heap[], int n);
void printHeap(int heap[], int n);

int main() {

	char command;
	int key, heap[100], n = 0;
	while (1) {
		scanf("%c", &command);
		if (command == 'i') {
			scanf("%d", &key);
			insertItem(key, heap, &n);
			printf("0\n");
		}
		else if (command == 'd') {
			printf("%d\n", removeMax(heap, &n));
		}
		else if (command == 'p') {
			printHeap(heap, n);
		}
		else if (command == 'q') {
			break;
		}
		getchar();
	}


	return 0;
}

void insertItem(int key, int heap[], int *n) {
	++(*n);
	heap[*n] = key;
	upHeap(*n, heap);
}

int removeMax(int heap[], int *n) {
	int key = heap[1];
	heap[1] = heap[*n];
	(*n)--;
	downHeap(1, heap, *n);
	return key;
}

void upHeap(int i, int heap[]) {
	if (i == 1)
		return;
	if (heap[i / 2] >= heap[i])
		return;
	int tmp = heap[i];
	heap[i] = heap[i / 2];
	heap[i / 2] = tmp;
	upHeap(i / 2, heap);
}

void downHeap(int i, int heap[], int n) {
	if ((n < (i * 2) && (n < (i * 2 + 1))))
		return;
	int bigger = i * 2;
	if (n >= i * 2 + 1)
		if (heap[i * 2 + 1] > heap[bigger])
			bigger = i * 2 + 1;
	if (heap[i] >= heap[bigger])
		return;
	int tmp = heap[i];
	heap[i] = heap[bigger];
	heap[bigger] = tmp;
	downHeap(bigger, heap, n);
}

void printHeap(int heap[], int n) {
	int i;
	for (i = 1; i < n + 1; i++)
		printf(" %d", heap[i]);
	printf("\n");
}

/*
[ 문제 2 ] 상향식 힙 생성
다음 프로그램을 작성해 상향식 힙 생성을 구현하라.
1) 이번엔 키들이 미리 한꺼번에 주어진다. 이들을 주어진 순서대로 초기 배열에 저장한다. 
2) 초기 배열에 저장된 키들을 상향식으로 재배치하여 힙을 생성한다. 상향식 힙 생성을 위한 재귀 또는 비재귀 방식의 알고리즘 가운데 어느 전략을 사용해도 좋다(사용하지 않은 나머지 전략도 나중에 작성해보자).
3) 참고로 재귀, 비재귀 두 가지 방식 모두 O(n) 시간에 수행 가능하므로(왜 그런지 복습하자) 그렇게 되도록 작성해야 한다. 
힌트: 문제 1 삽입식 힙 생성에서 이미 작성한 downHeap과 printHeap 함수를 그대로 사용하면 된다.
*/

#include<stdio.h>
#include<stdlib.h>

void rBuildHeap(int i, int heap[], int n);
void buildHeap(int heap[], int n);
void downHeap(int i, int heap[], int n);
void printHeap(int heap[], int n);

int main() {

	int keynum, num, i, heap[100], n = 0;
	scanf("%d", &keynum);
	getchar();
	for (i = 1; i <= keynum; i++) {
		scanf("%d", &num);
		heap[i] = num;
		n++;
	}
	buildHeap(heap, n);
	printHeap(heap, n);

	return 0;
}

void rBuildHeap(int i, int heap[], int n) {
	if (i > n)
		return;
	rBuildHeap(2 * i, heap, n);
	rBuildHeap(2 * i + 1, heap, n);
	downHeap(i, heap, n);
}

void buildHeap(int heap[], int n) {
	int i;
	for (i = n / 2; i > 0; i--) {
		downHeap(i, heap, n);
	}
}

void downHeap(int i, int heap[], int n) {
	if ((n < (i * 2) && (n < (i * 2 + 1))))
		return;
	int bigger = i * 2;
	if (n >= i * 2 + 1)
		if (heap[i * 2 + 1] > heap[bigger])
			bigger = i * 2 + 1;
	if (heap[i] >= heap[bigger])
		return;
	int tmp = heap[i];
	heap[i] = heap[bigger];
	heap[bigger] = tmp;
	downHeap(bigger, heap, n);
}

void printHeap(int heap[], int n) {
	int i;
	for (i = 1; i < n + 1; i++)
		printf(" %d", heap[i]);
	printf("\n");
}

/*
[ 문제 1 ] 힙 정렬 – 유일 키
다음 조건에 맞추어 힙 정렬 프로그램을 작성하라.
1) 순차힙으로 구현한다. 즉, 배열을 이용한 순차트리 형식으로 힙을 저장한다. 
2) 연산 효율을 위해 배열 인덱스 0 위치는 사용하지 않고 비워둔다. 
3) 데이터구조를 단순화하기 위해 힙의 항목으로써 (키, 원소) 쌍에서 원소를 생략하고 키만 저장하는 것으로 한다.
4) 키들은 중복이 없는 1 이상의 정수로 전제한다 – 즉, 중복 키에 대한 처리는 불필요하다. 
5) 최대 키 개수 < 100 으로 전제한다. 
6) 1기(힙 생성 단계)에서 삽입식 또는 상향식 가운데 어떤 방식을 사용해도 좋다. 
7) O(n log n) 시간, O(1) 공간에 수행해야 한다.
*/

#include<stdio.h>
#include<stdlib.h>

void insertItem(int key, int heap[], int *n);
void inPlaceHeapSort(int heap[], int n);
void printArray(int heap[], int n);
void upHeap(int i, int heap[]);
void downHeap(int i, int heap[], int n);
void rBuildHeap(int i, int heap[], int n);
void buildHeap(int heap[], int n);

int main() {

	int n = 0, key, i, heap[100], keynum;
	scanf("%d", &keynum);
	getchar();
	for (i = 1; i < keynum + 1; i++) {
		scanf("%d", &key);
		insertItem(key, heap, &n);
	}
	buildHeap(heap, n);
	inPlaceHeapSort(heap, n);
	printArray(heap, n);

	return 0;
}

void insertItem(int key, int heap[], int *n) {
	(*n)++;
	heap[*n] = key;
	upHeap(*n, heap);
}

void inPlaceHeapSort(int heap[], int n) {
	int i, tmp;

	for (i = n; i > 1; i--) {
		tmp = heap[1];
		heap[1] = heap[i];
		heap[i] = tmp;
		downHeap(1, heap, i - 1);
	}
}

void upHeap(int i, int heap[]) {
	if (i == 1)
		return;
	if (heap[i / 2] > heap[i])
		return;
	int tmp = heap[i];
	heap[i] = heap[i / 2];
	heap[i / 2] = tmp;
	upHeap(i / 2, heap);
}

void downHeap(int i, int heap[], int n) {
	if ((n < (i * 2) && (n < (i * 2 + 1))))
		return;
	int bigger = i * 2;
	if (n >= i * 2 + 1)
		if (heap[i * 2 + 1] > heap[bigger])
			bigger = i * 2 + 1;
	if (heap[i] > heap[bigger])
		return;
	int tmp = heap[i];
	heap[i] = heap[bigger];
	heap[bigger] = tmp;
	downHeap(bigger, heap, n);
}

void printArray(int heap[], int n) {
	int i;
	for (i = 1; i < n + 1; i++)
		printf(" %d", heap[i]);
	printf("\n");
}

void rBuildHeap(int i, int heap[], int n) {
	if (i > n)
		return;
	rBuildHeap(2 * i, heap, n);
	rBuildHeap(2 * i + 1, heap, n);
	downHeap(i, heap, n);
}

void buildHeap(int heap[], int n) {
	int i;
	for (i = n / 2; i > 0; i--) {
		downHeap(i, heap, n);
	}
}

/*
[ 문제 2 ] 힙 정렬 – 중복 키
중복 키를 처리할 수 있도록 작성된 알고리즘은 유일 키 환경에서도 정확히 작동한다. 하지만 유일 키를 처리할 수 있도록 작성된 알고리즘은 중복 키 환경에서도 정확히 작동한다는 보장이 없다. 
이번 문제는 문제 1에서 작성한 힙 정렬 관련 알고리즘들이 중복 키를 정확히 처리하는지 검증하고, 만약 부정확하다면 수정하는 것이다. 즉, 다음 조건 한 개를 제외하고는 문제 1과 동일하다.
1) 키들은 중복이 있을 수 있는 1 이상의 정수로 전제한다.
*/

void printArray(int heap[], int n);
void upHeap(int i, int heap[]);
void downHeap(int i, int heap[], int n);
void rBuildHeap(int i, int heap[], int n);
void buildHeap(int heap[], int n);

int main() {

	int n = 0, key, i, heap[100], keynum;
	scanf("%d", &keynum);
	getchar();
	for (i = 1; i < keynum + 1; i++) {
		scanf("%d", &key);
		insertItem(key, heap, &n);
	}
	buildHeap(heap, n);
	inPlaceHeapSort(heap, n);
	printArray(heap, n);

	return 0;
}

void insertItem(int key, int heap[], int *n) {
	(*n)++;
	heap[*n] = key;
	upHeap(*n, heap);
}

void inPlaceHeapSort(int heap[], int n) {
	int i, tmp;

	for (i = n; i > 1; i--) {
		tmp = heap[1];
		heap[1] = heap[i];
		heap[i] = tmp;
		downHeap(1, heap, i - 1);
	}
}

void upHeap(int i, int heap[]) {
	if (i == 1)
		return;
	if (heap[i / 2] >= heap[i])
		return;
	int tmp = heap[i];
	heap[i] = heap[i / 2];
	heap[i / 2] = tmp;
	upHeap(i / 2, heap);
}

void downHeap(int i, int heap[], int n) {
	if ((n < (i * 2) && (n < (i * 2 + 1))))
		return;
	int bigger = i * 2;
	if (n >= i * 2 + 1)
		if (heap[i * 2 + 1] > heap[bigger])
			bigger = i * 2 + 1;
	if (heap[i] >= heap[bigger])
		return;
	int tmp = heap[i];
	heap[i] = heap[bigger];
	heap[bigger] = tmp;
	downHeap(bigger, heap, n);
}

void printArray(int heap[], int n) {
	int i;
	for (i = 1; i < n + 1; i++)
		printf(" %d", heap[i]);
	printf("\n");
}

void rBuildHeap(int i, int heap[], int n) {
	if (i > n)
		return;
	rBuildHeap(2 * i, heap, n);
	rBuildHeap(2 * i + 1, heap, n);
	downHeap(i, heap, n);
}

void buildHeap(int heap[], int n) {
	int i;
	for (i = n / 2; i > 0; i--) {
		downHeap(i, heap, n);
	}
}

//합병정렬 퀵정렬

/*
[ 문제 1 ] (합병 정렬) n개의 양의 정수(중복 가능)를 입력받아 정렬하는 프로그램을 작성하시오. 정렬은 단일연결리스트를 이용하여 합병 정렬을 구현하여 사용한다. 
◦ 구현해야 할 합병 정렬 알고리즘: - 크기가 n인 단일연결리스트를 동적 할당하여, 입력된 양의 정수 저장(입력 정수는 중복 가능) 
- mergeSort(L) 함수: 단일연결리스트 L의 원소들을 합병 정렬하여 정렬된 결과를 오름차순으로 정렬
- merge(L1, L2) 함수: mergeSort에 호출되어 두 개의 정렬된 단일연결리스트 L1과 L2를 합병한 하나의 단일연결리스트를 반환. L1과 L2 합병을 위해 O(1)공간만 추가 사용 가능. 
- partition(L, k) 함수: 단일연결리스트 L과 양의 정수 k를 전달받아 L을 크기가 k이고 |L| – k인 두 개의 부리스트 L1과 L2로 분할하여 (L1, L2)를 반환. 
여기서 |L|은 L의 크기. 분할 시에도 주어진 L 공간 외에 O(1) 공간만 추가 사용 가능.
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	int data;
	struct node *next;
}NODE;

void partition(NODE *L, NODE **L1, NODE **L2, int k) {
	NODE *p = L;
	*L1 = L;
	int i;
	for (i = 0; i < k - 1; i++) {
		p = p->next;
	}
	*L2 = p->next;
	p->next = NULL;
}

NODE *merge(NODE **L1, NODE **L2) {
	NODE *p, *L;
	NODE *l1 = *L1, *l2 = *L2;
	if (l1->data <= l2->data) {
		L = l1;
		l1 = l1->next;
		p = L;
	}
	else {
		L = l2;
		l2 = l2->next;
		p = L;
	}
	while (l1 != NULL && l2 != NULL) {
		if (l1->data <= l2->data) {
			p->next = l1;
			l1 = l1->next;
			p = p->next;
		}
		else {
			p->next = l2;
			l2 = l2->next;
			p = p->next;
		}
	}
	while (l1 != NULL) {
		p->next = l1;
		l1 = l1->next;
		p = p->next;
	}
	while (l2 != NULL) {
		p->next = l2;
		l2 = l2->next;
		p = p->next;
	}
	return L;
}

void mergeSort(NODE **L, int n) {
	NODE *L1, *L2, *p = *L;
	if (n > 1) {
		partition(p, &L1, &L2, n / 2);
		if (n % 2 == 1) {
			mergeSort(&L1, n / 2);
			mergeSort(&L2, n - (n / 2));
		}
		else {
			mergeSort(&L1, n / 2);
			mergeSort(&L2, n / 2);
		}
		*L = merge(&L1, &L2);
	}
}

void addList(NODE **L, int value) {
	NODE *p = *L, *newnode = (struct node*)malloc(sizeof(struct node));
	newnode->data = value;
	newnode->next = NULL;
	if (*L == NULL)
		*L = newnode;
	else {
		while (p->next != NULL)
			p = p->next;
		p->next = newnode;
	}
}

void printList(struct node *L) {
	NODE *p = L;
	while (p != NULL) {
		printf(" %d", p->data);
		p = p->next;
	}
}

int main() {

	int n, value;
	NODE *L = NULL;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &value);
		addList(&L, value);
	}
	mergeSort(&L, n);
	printList(L);

	return 0;
}

/*
[문제 2] (퀵 정렬) n개의 양의 정수(중복 가능)를 입력받아 정렬하는 프로그램을 작성하시오. 정렬은 아래에 명시된 퀵 정렬을 구현하여 사용한다. 
◦ 구현해야 할 퀵 정렬 알고리즘: - 크기가 n인 배열을 동적 할당하여, 입력된 양의 정수 저장(입력 정수는 중복 가능). 
- 기준값(pivot)을 정할 때, 다음 방법을 이용한다:
(1) 부리스트의 수들 중 1개의 위치를 무작위로 선택(즉, 입력배열의 l과 r 사이의 1개 위치를 랜덤하게 선택)하여 pivot의 위치로 정한다. 
(2) 아래 힌트처럼 pivot의 위치를 정하는 findPivot 함수를 별도 작성해서 이 함수의 반환값을 inPlacePartition 함수가 사용하는 방식을 추천한다. 
- inPlacePartition의 반환값은 두 인덱스 (a, b)로, 
그 의미는 분할 결과, 배열의 l번째 수부터 a – 1번째 수는 pivot보다 작은 값을, 배열의 a번째부터 b번째 수는 pivot과 같은 값을, b + 1번째부터 r번째 수는 pivot보다 큰 값을 가진다는 것이다
(즉, 이후 호출되는 재귀함수는 l부터 a – 1까지 부배열에 대해서와 b + 1부터 r까지의 부배열에 대해서 다루고, pivot과 같은 값들인 a부터 b번째 값들은 재귀에서 제외된다).
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int findPivot(int *L, int l, int r) {
	int a, b, c;
	if (r - l <= 1)
		return l;
	srand((unsigned)time(NULL));
	a = (rand() % (r - l)) + l;
	b = (rand() % (r - l)) + l;
	c = (rand() % (r - l)) + l;
	if ((L[a] >= L[b] && L[a] <= L[c]) || (L[a] <= L[b] && L[a] >= L[c]))
		return a;
	else if ((L[a] <= L[b] && L[b] <= L[c]) || (L[a] >= L[b] && L[b] >= L[c]))
		return b;
	else
		return c;
}

int inPlacePartition(int *L, int l, int r, int k) {
	int i = l, j = r - 1, p = L[k], tmp;
	tmp = L[k];
	L[k] = L[r];
	L[r] = tmp;
	while (i <= j) {
		while (i <= j && L[i] <= p)
			i++;
		while (i <= j && L[j] >= p)
			j--;
		if (i < j) {
			tmp = L[i];
			L[i] = L[j];
			L[j] = tmp;
		}
	}
	tmp = L[i];
	L[i] = L[r];
	L[r] = tmp;

	j = r - 1;
	while (i <= j) {
		while (i <= j && L[i] == p)
			j--;
		if (i < j && L[i] == p) {
			tmp = L[i];
			L[i++] = L[j];
			L[j] = tmp;
		}
	}
	return i;
}

void inPlaceQuickSort(int *L, int l, int r) {
	int k, a, b, tmp;
	if (l >= r)
		return;
	k = findPivot(L, l, r);
	tmp = b = inPlacePartition(L, l, r, k);
	while (1) {
		if (L[tmp] != L[b]) {
			a = ++tmp;
			break;
		}
		tmp--;
	}
	inPlaceQuickSort(L, l, a - 1);
	inPlaceQuickSort(L, b + 1, r);
}

int main() {

	int i, n, *arr;
	scanf("%d", &n);
	arr = (int*)malloc(sizeof(int)*n);
	getchar();
	for (i = 0; i < n; i++)
		scanf("%d", &arr[i]);

	inPlaceQuickSort(arr, 0, n - 1);
	for (i = 0; i < n; i++)
		printf(" %d", arr[i]);
	free(arr);

	return 0;
}

//사전

/*
[ 문제 1 ] (이진탐색-재귀버전) 정렬되어 있는 n개의 정수 키(사전)와 탐색할 키 k를 입력받아, 사전에서 k의 위치를 출력하는 프로그램을 작성하시오. 
◦ 구현 조건
- 크기가 n인 배열을 동적 할당하여, 입력된 사전의 키 저장(중복 키는 없다고 가정) 
- 이진탐색을 이용하여 탐색 키의 위치 찾기 – O(log n) 시간 필요
- 재귀 버전으로 구현
- 가능하면 교재의 의사코드를 보지 말고 구현해볼 것을 권장 (단, 구현 후 본인의 코드를 교재의 코드와 꼭 비교해 볼 것)
◦ 출력
- x ≤ k 를 만족하는 사전의 키 x 중 가장 큰 값의 위치(즉, 인덱스) 출력
(위치는 0부터 시작한다고 가정하고, 위 조건을 만족하는 x가 없는 경우 –1 출력) 
- 즉, 키 k가 존재하는 경우에는 k의 위치를 출력하면 되고, 그렇지 않은 경우 k보다 작으면서 가장 큰 수의 위치를 출력하면 된다.
*/

#include<stdio.h>
#include<stdlib.h>

int rFindElement(int *key, int k, int l, int r) {
	if (l > r)
		return r;
	int mid = (l + r) / 2;
	if (k == key[mid])
		return mid;
	else if (k < key[mid])
		return rFindElement(key, k, l, mid - 1);
	else
		return rFindElement(key, k, mid + 1, r);
}

int main() {

	int n, k, *x, i, element;
	scanf("%d %d", &n, &k);
	getchar();
	x = (int*)malloc(n * sizeof(int));
	for (i = 0; i < n; i++)
		scanf("%d", &x[i]);

	element = rFindElement(x, k, 0, n - 1);
	printf(" %d", element);

	free(x);

	return 0;
}

/*
[ 문제 2 ] (이진탐색-비재귀버전) 정렬되어 있는 n개의 정수 키(사전)와 탐색할 키 k를 입력받아, 사전에서 k의 위치를 출력하는 프로그램을 작성하시오. 
◦ 구현 조건
- 비재귀 버전(즉, 반복 버전)으로 구현
- 나머지 조건은 문제 1과 동일
◦ 출력 (문제 1과 약간 다름에 주의) 
- x ≥ k 를 만족하는 사전의 키 x 중 가장 작은 값의 위치(즉, 인덱스) 출력
(위치는 0부터 시작한다고 가정하고, 위 조건을 만족하는 x가 없는 경우 n 출력)
*/

#include<stdio.h>
#include<stdlib.h>

int FindElement(int *list, int key, int l, int r) {
	int mid;
	while (l <= r) {
		mid = (l + r) / 2;
		if (key <= list[mid])
			r = mid - 1;
		else
			l = mid + 1;
	}
	return l;
}

int main() {

	int n, k, *x, i, element;
	scanf("%d %d", &n, &k);
	getchar();
	x = (int*)malloc(n * sizeof(int));
	for (i = 0; i < n; i++)
		scanf("%d", &x[i]);

	element = FindElement(x, k, 0, n - 1);
	printf(" %d", element);

	free(x);

	return 0;
}

/*
[ 문제 3 ] (이진탐색 응용) 세종이는 친구와 이진탐색을 응용한 숫자 맞추기 게임을 하고 있다. 세종이를 도와 정답을 찾는 프로그램을 작성하시오. 
게임 규칙:
① 친구는 두 개의 양의 정수 a와 b를 선택하고 세종이에게 알려준다. 단, a < b. ② 친구는 a ≤ k ≤ b를 만족하는 정수 k를 하나 선택한다. (k는 세종이에게 알려주지 않는다.)
③ 친구는 세종이에게 다음 정보를 알려준다. (이진 탐색) - 친구는 세종이에게 k > m 인지, Y(예)/N(아니오)으로 알려준다. (여기서 m은 a와 b사이의 중간값으로, m =(a + b)/2이다. 는 내림 기호) - 답이 Y인 경우, m + 1 ≤ k ≤ b 이므로 a의 값을 m + 1로 바꾼다. 답이 N인 경우, a ≤ k ≤ m 이므로 b를 m으로 바꾼다. - 위 과정을 a와 b가 같을 때까지 반복한다. 예) a = 10, b = 20이고, ③에서 주어지는 정보가 NNY인 경우
1) k > 15 인가? → 답) N ➜ 10 ≤ k ≤ 15
2) k > 12 인가? → 답) N ➜ 10 ≤ k ≤ 12
3) k > 11 인가? → 답) Y ➜ 12 ≤ k ≤ 12 (즉, k = 12)
프로그램 구현:
◦ 입력 정보 : 친구가 세종이에게 알려주는 정보가 입력으로 주어진다. - ①에서 주어지는 수의 범위를 나타내는 양의 정수 a와 b
- ③에서 주어지는 대문자 Y와 N으로 구성된 공백 없는 문자열
(k를 찾기 위한 정확한 수의 답이 주어진다고 가정)
힌트: 문자열의 문자를 하나씩 읽어 처리하면 된다(배열 필요 없음).
◦ 출력 정보
- 친구가 선택한 수 k
◦ 도움말
- 이진탐색은 재귀 혹은 비재귀 중 어떤 방식을 사용해도 무방하다.
*/

#include<stdio.h>
#include<stdlib.h>

int main() {

	int l, r, k, i, mid;
	char c;
	scanf("%d %d %d", &l, &r, &k);
	getchar();
	for (i = 0; i < k; i++) {
		scanf("%c", &c);
		mid = (l + r) / 2;
		if (c == 'Y')
			l = mid + 1;
		else if (c == 'N')
			r = mid;
		if (l == r) {
			printf("%d", l);
			break;
		}
	}

	return 0;
}