/*
[ 문제 1 ] (분리연쇄법 해시테이블) 크기 M인 해시테이블에 여러 개의 키 값을 입력받아
저장하고, 분리연쇄법을 이용하여 충돌을 처리하는 해시테이블 프로그램을 작성하시오.
◦ 구현 조건
 - 해시테이블은 크기가 M인 배열로 동적 할당한다.
 - 입력 키는 중복이 없는 자연수다.
 - 키 x에 대한 해시함수 h(x) = x % M 을 사용한다.
 - 삽입 시 충돌이 발생하는 경우, 해당 버켓 리스트의 맨 앞에 삽입한다.
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	int key;
	struct node *next;
}NODE;

int h(int x, int m) {
	return x % m;
}

void insertKey(NODE *hashTable, int key, int m) {
	int bucket = h(key, m);
	NODE* newnode = (NODE*)malloc(sizeof(NODE));
	newnode->key = key;
	newnode->next = hashTable[bucket].next;
	hashTable[bucket].next = newnode;
}

int findKey(NODE *hashTale, int key, int m) {
	int bucket = h(key, m), cnt = 0;
	NODE *tmp = &hashTale[bucket];
	while (tmp->next != NULL) {
		tmp = tmp->next;
		cnt++;
		if (tmp->key == key)
			return cnt;
	}
	return 0;
}

int removeKey(NODE *hashTable, int key, int m) {
	int bucket = h(key, m), cnt = 0;
	NODE *first = &hashTable[bucket], *last = first;
	while (first->next != NULL) {
		first = first->next;
		cnt++;
		if (first->key == key) {
			last->next = first->next;
			free(first);
			return cnt;
		}
		last = first;
	}
	return 0;
}

void printTable(NODE *hashTable, int m) {
	NODE *tmp;
	int i;
	for (i = 0; i < m; i++) {
		tmp = &hashTable[i];
		while (tmp->next != NULL) {
			tmp = tmp->next;
			printf(" %d", tmp->key);
		}
	}
}

int main() {

	NODE *hashTable;
	char cmd;
	int i, m, key;
	scanf("%d", &m);
	hashTable = (NODE*)malloc(sizeof(NODE) * m);
	for (i = 0; i < m; i++) {
		hashTable[i].key = i;
		hashTable[i].next = NULL;
	}
	while (1) {
		scanf("%c", &cmd);
		if (cmd == 'i') {
			scanf("%d", &key);
			insertKey(hashTable, key, m);
		}
		else if (cmd == 's') {
			scanf("%d", &key);
			printf("%d\n", findKey(hashTable, key, m));
		}
		else if (cmd == 'd') {
			scanf("%d", &key);
			printf("%d\n", removeKey(hashTable, key, m));
		}
		else if (cmd == 'p') {
			printTable(hashTable, m);
			printf("\n");
		}
		else if (cmd == 'e')
			break;
	}
	return 0;
}

/*
[ 문제 2 ] (개방주소법 해시테이블 – 선형조사법) 크기 M인 해시테이블에 n개의 키 값을 입력받아 저장하고,
개방주소법 중 선형조사법을 이용하여 충돌을 처리하는 해시테이블 프로그램을 작성하시오.
◦ 구현 조건
- 해시테이블은 크기가 M인 배열로 동적 할당한다. - n은 M보다 작은 자연수로 최대 삽입 개수다.
- 입력 키는 중복이 없는 6자리 또는 8자리의 임의의 자연수(학번)다.
- 키 x에 대한 해시함수 h(x) = x % M 을 사용한다.
- 저장된 키 값이 없는 빈 버켓은 0으로 처리한다.
*/

#include<stdio.h>
#include<stdlib.h>

int h(int key, int m) {
	return key % m;
}

void insertKey(int *hashTable, int key, int m) {
	int bucket = h(key, m);
	while (hashTable[h(bucket, m)] != 0) {
		printf("C");
		bucket++;
	}
	hashTable[h(bucket, m)] = key;
	printf("%d\n", bucket % m);
}

void findKey(int *hashTable, int key, int m) {
	int v = h(key, m), bucket = h(key, m);
	while (hashTable[h(bucket, m)] != key) {
		bucket++;
		if (h(bucket, m) == v) {
			printf("-1");
			return;
		}
	}
	printf("%d %d\n", h(bucket, m), hashTable[h(bucket, m)]);
}

int main() {

	char cmd;
	int *hashTable, i = 0, m, n, key, bucket;
	scanf("%d %d", &m, &n);
	hashTable = (int*)malloc(sizeof(int)*m);
	while (1) {
		scanf("%c", &cmd);
		if (cmd == 'i') {
			scanf("%d", &key);
			if (i >= n)
				continue;
			insertKey(hashTable, key, m);
			i++;
		}
		else if (cmd == 's') {
			scanf("%d", &key);
			findKey(hashTable, key, m);
		}
		else if (cmd == 'e')
			break;
	}

	return 0;
}

/*
[ 문제 3 ] (개방주소법 해시테이블 – 이중해싱) 문제 2에서 충돌처리 방법을 이중해싱으로 변경하시오.
◦ 구현 조건
 - 해시테이블은 크기가 M인 배열로 동적 할당한다(종료 시 해제).
 - n은 M보다 작은 자연수로 최대 삽입 개수다.
 - 입력 키는 중복이 없는 2자리 이상의 자연수다.
 - 키 x에 대한 첫 번째 해시함수 h(x) = x % M, 두 번째 해시함수 h‘(x) = q – (x % q) 를 사용한다. q는 M보다 조금 작은 소수로 입력으로 주어진다.
- 저장된 키가 없는 빈 버켓은 0으로 처리한다.
*/

#include<stdio.h>
#include<stdlib.h>

int h(int key, int m) {
	return key % m;
}

int h2(int key, int q) {
	return q - (key % q);
}

void insertKey(int *hashTable, int key, int m, int q) {
	int bucket = h(key, m);
	while (hashTable[h(bucket, m)] != 0) {
		printf("C");
		bucket += h2(key, q);
	}
	hashTable[h(bucket, m)] = key;
	printf("%d\n", h(bucket, m));
}

void findKey(int *hashTable, int key, int m, int q) {
	int cnt = 0, bucket = h(key, m);
	while (hashTable[h(bucket, m)] != key) {
		bucket += h2(key, q);
		cnt++;
		if (cnt >= m) {
			printf("-1\n");
			return;
		}
	}
	printf("%d %d", h(bucket, m), hashTable[h(bucket, m)]);
}

void printTable(int *hashTable, int m) {
	int i;
	for (i = 0; i < m; i++)
		printf(" %d", hashTable[i]);
	printf("\n");
}

int main() {

	char cmd;
	int *hashTable, i = 0, m, n, q, key, bucket;
	scanf("%d %d %d", &m, &n, &q);
	hashTable = (int*)malloc(sizeof(int)*m);
	while (1) {
		scanf("%c", &cmd);
		if (cmd == 'i') {
			if (i >= n)
				continue;
			scanf("%d", &key);
			insertKey(hashTable, key, m, q);
			i++;
		}
		else if (cmd == 's') {
			scanf("%d", &key);
			findKey(hashTable, key, m, q);
		}
		else if (cmd == 'p')
			printTable(hashTable, m);
		else if (cmd == 'e') {
			printTable(hashTable, m);
			break;
		}
	}
	free(hashTable);

	return 0;
}