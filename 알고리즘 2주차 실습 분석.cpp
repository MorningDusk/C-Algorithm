/*
[ 문제 1 ] 나머지 연산
‘%’(modulo) 연산자는 나눗셈의 나머지를 반환한다. 덧셈과 뺄셈 연산자만을 사용하여 a를 b로 나눈 나머지를 반환하는 modulo(a, b) 함수와 이를 테스트할 프로그램을 작성하시오. 
단, a ≥ 0, b > 0 인 정수다.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int modulo(int a, int b) {
	int c = a - b;

	while (c > 0) {
		c -= b;
	}

	if (c != 0) {
		c += b;
	}
	return c;
}

int main() {

	int a, b, c;
	scanf("%d %d", &a, &b);

	c = modulo(a, b);
	printf("%d", c);

}

/*
[ 문제 2 ] 비트행렬에서 최대 1행 찾기
n × n 비트 행렬 A의 각 행은 1과 0으로만 구성되며, A의 어느 행에서나 1들은 해당 행의 0들보다 앞서 나온다고 가정하자. 
행렬 A를 입력받아, 가장 많은 1을 포함하는 행을 찾는 프로그램을 작성하시오. 
그러한 행이 여러 개 있을 경우 그 가운데 가장 작은 행 번호를 찾아야한다.

Alg mostOnesButSlow(A, n)					{slow version}
	input bit matrix A[n × n]
	output the row of A with most 1’s

1. row, jmax ← 0
2. for i ← 0 to n – 1
		j ← 0
		while ((j < n) & (A[i, j] = 1))
			j ← j + 1
		if (j > jmax)
			row ← i
			jmax ← j
3. return row							{Total O(n2)}
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mostOnes(int **arr, int n) {
	int i = 0, j = 0, row = 0;

	while ((i < n) && (j < n)) {
		if (arr[i][j] == 0) {
			i++;
		}
		else {
			row = i;
			j++;
		}
	}
	return row;
}

int main() {
	int n;
	int ** arr;

	scanf("%d", &n);
	arr = (int **)malloc(sizeof(int*) * n);

	for (int i = 0; i < n; i++) {
		arr[i] = (int *)malloc(sizeof(int)*n);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			scanf("%d", &arr[i][j]);
	}

	printf("%d", mostOnes(arr, n));

	for (int i = 0; i < n; i++)
		free(arr[i]);
	free(arr);
}

/*
[ 문제 3 ] 누적 평균
원시 데이터값들로 구성된 배열 X의 i-번째 누적평균(prefix average)이란 X의 i-번째에 이르기까지의 (i + 1)개 원소들의 평균이다. 즉,
	  A[i] = (X[0] + X[1] + … + X[i])/(i + 1)
누적평균은 경제, 통계 분야에서 오르내림 변동을 순화시킴으로써 대략적 추세를 얻어내기 위해 사용된다. 일례로 부동산, 주식, 펀드 등에도 자주 활용된다.
이 문제는 배열 X의 누적평균(prefix average) 배열 A를 구하는 프로그램을 구현하고 테스트하는데 관한 것이다.

Alg prefixAverages1(X, n)		{ver.1}
	input array X of n integers
	output array A of prefix averages of X

1. for i ← 0 to n – 1				{n}
		sum ← 0	 						{n}
		for j ← 0 to i				{1 + 2 + … + n}
			sum ← sum + X[j]		{1 + 2 + … + n}
		A[i] ← sum/(i + 1)			{n}
2. return A								{1}
											{Total O(n2)}
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *prefixAverages1(int X[], int n) {
	float sum;
	int *A, i, j;
	A = (int *)malloc(n * sizeof(int));

	for (i = 0; i < n; i++) {
		sum = 0;
		for (j = 0; j <= i; j++)
			sum += X[j];
		A[i] = (sum / (i + 1) + 0.5) / 1;
	}
	return A;
}

int *prefixAverages2(int Y[], int n) {
	float sum = 0;
	int *A, i;
	A = (int *)malloc(n * sizeof(int));

	for (i = 0; i < n; i++) {
		sum += Y[i];
		A[i] = (sum / (i + 1) + 0.5) / 1;
	}
	return A;
}


int main() {

	int n, i, *A, *X, *Y;
	scanf("%d", &n);
	A = (int *)malloc(n * sizeof(int));
	for (i = 0; i < n; i++)
		scanf("%d", &A[i]);

	X = prefixAverages1(A, n);
	Y = prefixAverages2(A, n);
	for (i = 0; i < n; i++)
		printf("%d ", X[i]);
	printf("\n");
	for (i = 0; i < n; i++)
		printf("%d ", Y[i]);

	free(A);

	return 0;
}