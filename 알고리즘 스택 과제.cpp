#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>

int stacksize, top;

void push(int *stack, int n) {
	stack = (int*)realloc(stack, ++stacksize);
	stack[++top] = n;
}

void pushMillion(int *stack) {
	int i;
	stack = (int*)realloc(stack, stacksize += 1000000);

	for (i = top; i < top + 100000; i++)
		stack[i] = rand() % 10000;
}

int pop(int *stack) {
	if (top < 0) {
		printf("Stack empty\n");
		return -1;
	}
	--stacksize;
	stack = (int*)realloc(stack, stacksize);
	return stack[top--];
}

void popMillion(int *stack) {
	int i;
	if (top < 0)
		return;
	for (i = top + 1000000 - 1; i >= top; i--)
		stack[i] = NULL;
	stacksize -= 1000000;
	stack = (int*)realloc(stack, stacksize);
}

int findMin(int *stack) {
	int i, min = stack[0];

	for (i = 0; i < stacksize; i++)
		if (min > stack[i])
			min = stack[i];
	return min;
}

int main() {

	int i, n, *stack = (int*)malloc(sizeof(int));
	char command;
	LARGE_INTEGER ticksPerSec, start, end, diff;

	top = -1;
	stacksize = 0;
	QueryPerformanceFrequency(&ticksPerSec);
	srand((unsigned)time(NULL));

	while (1) {
		scanf("%c", &command);
		if (command == 'p') {
			scanf("%d", &n);
			QueryPerformanceCounter(&start);
			push(stack, n);
			QueryPerformanceCounter(&end);
			diff.QuadPart = end.QuadPart - start.QuadPart;
			printf("push %d (%d), cputime = %lf\n", n, stacksize, ((double)diff.QuadPart/(double)ticksPerSec.QuadPart));
		}
		else if (command == 'P') {
			QueryPerformanceCounter(&start);
			pushMillion(stack);
			QueryPerformanceCounter(&end);
			diff.QuadPart = end.QuadPart - start.QuadPart;
			printf("pushMillion (%d), cputime = %lf\n", stacksize, ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
		}
		else if (command == 'o') {
			QueryPerformanceCounter(&start);
			n = pop(stack);
			QueryPerformanceCounter(&end);
			diff.QuadPart = end.QuadPart - start.QuadPart;
			printf("pop %d (%d), cputime = %lf\n", n, stacksize, ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
		}
		else if (command == 'O') {
			QueryPerformanceCounter(&start);
			popMillion(stack);
			QueryPerformanceCounter(&end);
			diff.QuadPart = end.QuadPart - start.QuadPart;
			printf("popMillion (%d), cputime = %lf\n", stacksize, ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
		}
		else if (command == 'f') {
			QueryPerformanceCounter(&start);
			n = findMin(stack);
			QueryPerformanceCounter(&end);
			diff.QuadPart = end.QuadPart - start.QuadPart;
			printf("min %d (%d), cputime = %lf\n", n, stacksize, ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
		}
		else if (command == 'q')
			break;
	}

	return 0;
}

/*

4
10
POP
PUSH s
PUSH t
PUSH a
PUSH r
PRINT
UpR 3
PRINT
PUSH s
PEEK

5
11
PUSH s
PUSH r
PUSH a
PUSH t
PUSH s
PRINT
DownR 4
PRINT
POP
POP
PRINT

*/