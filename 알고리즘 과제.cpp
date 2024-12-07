//힙과 힙정렬

/*
[ 문제 1 ] (50) 주어진 숫자들이 나타내는 완전이진트리가 min-heap인지 아닌지 체크하는 프로그램을 작성하여라. 
min-heap이면 Yes, min-heap이 아니면 No를 출력하고, 마지막 내부노드의 값을 출력한다. 편의상 중복숫자는 없다고 가정한다. 불필요한 비교를 남발하면 감점.
내부노드가 하나도 없는 경우는 없다.
*/

#include<stdio.h>
#include<stdlib.h>

int main() {

	int key, arr[100], i, check = 0, keyn;		//변수 선언
	scanf("%d", &keyn);		//heap의 노드 수 선언
	getchar();		//엔터키 제거

	for (i = 1; i <= keyn; i++)
		scanf("%d", &arr[i]);		//정수 입력

	for (i = 1; i <= keyn / 2; i++) {		//배열 검사
		if (arr[i] > arr[i * 2] || arr[i] > arr[i * 2 + 1]) {		//자식이 부모보다 크다면
			check++;		//check 변수에 1 더한다
		}
	}


	if (check == 0)		//check 변수가 0이면
		printf("Yes\n");		//최소 힙이 맞다고 선언
	else		//check 변수가 0보다 크면
		printf("No\n");		//최소 힙이 아니라고 선언

	printf("%d", arr[keyn / 2]);		//마지막 내부노드의 값 출력

	return 0;
}

/*
[ 문제 2 ] (50) 양의 정수 N과 N개의 정수가 입력이 된다. (K개의 노드만 갖는 힙을 사용하여 N개 중 K개 큰 값들을 출력하려고 한다(K<=N). 
힙을 위하여 (K+1)개 힙노드만 동적 할당하여야 한다. 힙을 사용하여 작업을 하면 정렬 되지 않은 K개의 큰 값들이 결과로 나오는데, OJ에서의 채점을 위하여 오름차순으로 정렬하여 출력하여라. 
(중복은 없다고 가정한다.)
*/

#include<stdio.h>
#include<stdlib.h>

void upHeap(int i, int heap[]) {		//upHeap 알고리즘 선언
	if (i == 1)		//위치가 처음이면
		return;		//종료
	if (heap[i / 2] < heap[i])		//부모보다 자식이 크면
		return;		//종료
	int tmp = heap[i];		//값을 교환한다
	heap[i] = heap[i / 2];
	heap[i / 2] = tmp;
	upHeap(i / 2, heap);		//다른 위치로 재귀
}

void downHeap(int i, int heap[], int n) {		//downHeap 알고리즘 선언
	int left = i * 2, right = i * 2 + 1;		//변수 선언
	if ((n < left && n < right))		//위치가 부모위치가 아니면
		return;		//종료
	int smaller = left;		//작은 수를 왼쪽 자식으로 설정
	if (n >= right)		//위치가 오른쪽 자식보다 같거나 크면
		if (heap[right] < heap[smaller])		//작은 수가 오른쪽 자식보다 크면
			smaller = right;		//값 갱신
	if (heap[i] < heap[smaller])		//더 작은 값이 존재하면
		return;		//종료
	int tmp = heap[i];		//값을 교환한다
	heap[i] = heap[smaller];
	heap[smaller] = tmp;
	downHeap(smaller, heap, n);		//작은 수 위치로 재귀
}

void buildHeap(int heap[], int n) {		//재귀적 하향식 힙 생성
	int i;
	for (i = n / 2; i >= 1; i--)
		downHeap(i, heap, n);
}

int main() {

	int n, k, i, *heap, j, key, m, tmp;		//변수 선언
	scanf("%d %d", &n, &k);		//변수 입력
	getchar();
	heap = (int*)malloc(sizeof(int)*(k + 1));		//힙 크기 할당
	for (i = 1; i <= k; i++)
		scanf("%d", &heap[i]);		//힙 값 입력
	buildHeap(heap, k);		//힙 생성

	m = n - k;
	while (m > 0) {
		scanf("%d", &key);		//추가 값 입력
		if (key > heap[1])
			heap[1] = key;
		buildHeap(heap, k);
		m--;
	}

	for (i = 1; i <= k - 1; i++)
		for (j = i + 1; j <= k; j++) {
			if (heap[i] > heap[j]) {
				tmp = heap[i];
				heap[i] = heap[j];
				heap[j] = tmp;
			}
		}

	for (i = 1; i <= k; i++)
		printf("%d ", heap[i]);

	return 0;
}

//합병정렬 퀵정렬

/*
[문제 1] (퀵 정렬) n개의 양의 정수(중복 가능)를 입력받아 정렬하는 프로그램을 작성하시오. 정렬은 아래에 명시된 퀵 정렬을 구현하여 사용한다. 
◦ 구현해야 할 퀵 정렬 알고리즘: 
- 크기가 n인 배열을 동적 할당하여, 입력된 양의 정수 저장(입력 정수는 중복 가능). 
- 기준값(pivot)을 정할 때, 다음 방법을 이용한다:
(1) 부리스트의 수들 중 1개의 위치를 무작위로 선택(즉, 입력배열의 l과 r 사이의 1개 위치를 랜덤하게 선택)하여 pivot의 위치로 정한다. 
(2) 아래 힌트처럼 pivot의 위치를 정하는 findPivot 함수를 별도 작성해서 이 함수의 반환값을 inPlacePartition 함수가 사용하는 방식을 추천한다.
- inPlacePartition의 반환값은 두 인덱스 (a, b)로, 그 의미는 분할 결과, 배열의 l번째 수부터 a – 1번째 수는 pivot보다 작은 값을, 배열의 a번째부터 b번째 수는 pivot과 같은 값을, 
b + 1번째부터 r번째 수는 pivot보다 큰 값을 가진다는 것이다
(즉, 이후 호출되는 재귀함수는 l부터 a – 1까지 부배열에 대해서와 b + 1부터 r까지의 부배열에 대해서 다루고, pivot과 같은 값들인 a부터 b번째 값들은 재귀에서 제외된다).
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int findPivot(int *L, int l, int r) {		//findPivot 함수 선언
	int a, b, c;		//변수 선언
	if (r - l < 0)		//왼쪽과 오른쪽 사이 간격이 매우 작다면
		return l;		//맨 왼쪽 위치 정수 반환 
	srand(time(NULL));		//랜덤으로 정수 뽑기 위해 선언
	a = (rand() % (r - l)) + l;		//3개의 랜덤 정수를 뽑는다
	b = (rand() % (r - l)) + l;
	c = (rand() % (r - l)) + l;
	if ((L[a] >= L[b] && L[a] <= L[c]) || (L[a] <= L[b] && L[a] >= L[c]))		//a가 b보다 크고 c보다 작다면 또는 그 반대라면
		return a;		//a값 반환
	else if ((L[a] <= L[b] && L[b] <= L[c]) || (L[a] >= L[b] && L[b] >= L[c]))		//b가 a보다 크고 c보다 작다면 또는 그 반대라면
		return b;		//b값 반환
	else		//c가 a보다 크고 b보다 작다면 또는 그 반대라면
		return c;		//c값 반환
}

int inPlacePartition(int *L, int l, int r, int k) {		//inParitition 함수 선언
	int i, j, p, tmp;		//변수 선언
	p = L[k];		//pivot 설정
	tmp = L[k];		//pivot를 맨 오른쪽 값과 교환해서 잠시 숨긴다
	L[k] = L[r];
	L[r] = tmp;
	i = l;		//i를 맨 왼쪽 위치로 설정
	j = r - 1;		//j를 거의 맨 오른쪽 위치로 설정
	while (i <= j) {		//이 두 사이 위치 내
		while (i <= j && L[i] <= p)		//값이 pivot보다 작다면
			i++;		//점점 오른쪽으로 옮긴다
		while (i <= j && L[j] >= p)		//값이 pivot보다 크다면
			j--;		//점점 왼쪽으로 옮긴다
		if (i < j) {		//왼쪽 값이 오른쪽보다 작다면
			tmp = L[i];		//값을 교환한다
			L[i] = L[j];
			L[j] = tmp;
		}
	}
	tmp = L[i];		//피벗을 제자리로 옮긴다
	L[i] = L[r];
	L[r] = tmp;

	j = r - 1;		//피벗 위치를 2개 설정해야 하기 때문에 오른쪽 값 다시 설정
	while (i <= j) {		//이 두 사이 위치 내
		while (i <= j && L[i] == p)		//값이 pivot과 같다면
			j--;		//점점 왼쪽으로 옮긴다
		if (i < j && L[i] == p) {		//왼쪽 값이 오른쪽보다 작고 왼쪽 값이 pivot과 같다면
			tmp = L[i];		//교환하면서 위치 오른쪽으로 이동
			L[i++] = L[j];
			L[j] = tmp;
		}
	}
	return i;		//pivot의 위치 정수 반환
}

void inPlaceQuickSort(int *L, int l, int r) {		//inPlaceQuickSort 함수 선언
	int k, a, b, tmp;		//변수 선언
	if (l >= r)		//왼쪽 값이 오른쪽 값보다 크면
		return;		//종료
	k = findPivot(L, l, r);		//findPivot 함수를 써서 pivot 값 설정
	tmp = b = inPlacePartition(L, l, r, k);		//pivot의 위치 값 설정
	while (1) {
		if (L[tmp] != L[b]) {		//pivot 위치값이 같지 않다면
			a = ++tmp;		//자리를 옮기고 종료
			break;
		}
		tmp--;		//위치 이동
	}
	inPlaceQuickSort(L, l, a - 1);		//재귀 inPlaceQuickSort로 LT, GT 생성하여 다시 실행
	inPlaceQuickSort(L, b + 1, r);
}

int main() {

	int i, n, *arr;		//변수 선언
	scanf("%d", &n);		//크기 값 입력
	arr = (int*)malloc(sizeof(int)*n);		//동적할당
	getchar();
	for (i = 0; i < n; i++)
		scanf("%d", &arr[i]);		//리스트 값 입력

	inPlaceQuickSort(arr, 0, n - 1);		//inPlaceQuickSort 함수 실행
	for (i = 0; i < n; i++)
		printf(" %d", arr[i]);		//정렬된 값 입력
	free(arr);

	return 0;
}