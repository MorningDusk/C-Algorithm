/*
[ 문제 1 ] N(3 ≤ N ≤ 100)개의 정수로 이루어진 수열 X를 “뒤집기 정보”에 의해 변환한 최종 결과를 출력하는 프로그램을 작성하시오.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

	int n, ir, a, b, i, j, k, *x = NULL, tmp;

	scanf("%d", &n);
	getchar();
	x = (int *)malloc(n * sizeof(int));
	for (i = 0; i < n; i++)
		scanf("%d", &x[i]);
	scanf("%d", &ir);

	for (i = 0; i < ir; i++) {
		scanf("%d %d", &a, &b);
		k = 0;
		for (j = a; j < (a + b) / 2 + 1; j++) {
			tmp = x[b - k];
			x[b - k] = x[j];
			x[j] = tmp;
			k++;
		}
	}

	for (i = 0; i < n; i++)
		printf(" %d", x[i]);

	free(x);

	return 0;
}

/*
[ 문제 2 ] N(2 ≤ N ≤ 100)개의 정수로 이루어진 수열 X를 “위치 바꿈 정보”에 의해 변환한 최종 결과를 출력하는 프로그램을 작성하시오.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

	int n, m, *x, *s, i, tmp1, tmp2;
	scanf("%d", &n);
	getchar();
	x = (int *)malloc(n * sizeof(int));
	for (i = 0; i < n; i++)
		scanf("%d", &x[i]);
	scanf("%d", &m);
	s = (int *)malloc(m * sizeof(int));
	for (i = 0; i < m; i++)
		scanf("%d", &s[i]);

	tmp1 = x[s[0]];
	for (i = 1; i < m; i++) {
		tmp2 = x[s[i]];
		x[s[i]] = tmp1;
		tmp1 = tmp2;
	}

	for (i = 0; i < n; i++)
		printf(" %d", x[i]);

	free(x);
	free(s);

	return 0;
}

/*
[ 문제 3 ] N x N (1 ≤ N ≤ 100) 크기의 행렬에 1 ~ N² 의 수를 아래 그림과 같이 차례로 위에서부터 → 방향과 ← 방향을 번갈아 가면서 채운 결과를 출력하시오.
*/

int main() {

	int n, num = 1, i, j;
	scanf("%d", &n);

	for (i = 0; i < n; i++) {
		if (i % 2) {
			num += n;
			for (j = 1; j <= n; j++)
				printf(" %d", num - j);
		}
		else {
			for (j = 0; j < n; j++)
				printf(" %d", num++);
		}
		printf("\n");
	}


	return 0;
}

/*
[ 문제 4 ] N x M (1 ≤ N, M ≤ 100) 크기의 행렬에 1 ~ MN 의 수를 아래 그림과 같이 나선형으로 채운 결과를 출력하시오.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int arr[100][100];
	int size_x, size_y;
	int save_size_x, save_size_y;
	int i, j;
	int x = 0, y = -1, turn = 1;
	int num = 1;
	int max_num = 0;

	scanf("%d %d", &size_x, &size_y);

	max_num = size_x * size_y;

	save_size_x = size_x;
	save_size_y = size_y;


	while (num != max_num + 1) {
		for (i = 1; i <= save_size_y; i++) {
			y += turn;
			arr[x][y] = num;
			num++;
		}

		save_size_x--;

		for (i = 1; i <= save_size_x; i++) {
			x += turn;
			arr[x][y] = num;
			num++;
		}
		turn *= -1;

		save_size_y--;
	}

	for (i = 0; i < size_x; i++) {
		for (j = 0; j < size_y; j++)
		{
			printf(" %d", arr[i][j]);
		}
		printf("\n");
	}
	return 0;
}

/*
[ 문제 5 ] N x M (1 ≤ N, M ≤ 100) 크기의 행렬에 1 ~ MN 의 수를 아래 그림과 같이 ↙ 대각선 방향으로 채운 결과를 출력하시오.
*/

#include <stdio.h>

int main() {
	int arr[101][101] = { 0 };
	int i, j, k = 0, m, n;
	int spin;
	scanf("%d %d", &n, &m);

	if (n == 1) {
		for (i = 0; i < m; i++) {
			k++;
			arr[0][i] = k;
		}
	}
	else if (m == 1) {
		for (i = 0; i < n; i++) {
			k++;
			arr[i][0] = k;
		}
	}
	else {
		for (spin = 2; spin <= (m * n); spin++) {
			for (i = 1; i <= n; i++) {
				j = spin - i;
				if (j <= m && j > 0) {
					++k;
					arr[i - 1][j - 1] = k;

				}
			}
		}
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++)
			printf(" %d", arr[i][j]);
		printf("\n");
	}

	return 0;
}
