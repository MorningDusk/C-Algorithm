/*
[ 문제 1 ] 양의 정수 N을 입력받아, 1부터 N까지의 합을 구하는 프로그램을 작성하시오.
*/

#include <stdio.h>
#include <stdlib.h>

int sum(int n) {
	if (n == 1)
		return 1;
	else
		return n + sum(n - 1);
}

int main() {

	int n, res = 0;

	scanf("%d", &n);

	res = sum(n);

	printf("%d", res);

	return 0;
}

/*
 문제 2 ] 양의 정수를 입력받아, 각 자리의 수를 높은 자릿수부터 차례로 출력하는 프로그램을 작성하시오.
*/

#include <stdio.h>
#include <stdlib.h>

void Divide(int n) {
	if (n < 10)
		printf("%d\n", n);
	else {
		Divide(n / 10);
		printf("%d\n", n % 10);
	}
}

int main() {

	int n, res = 0;
	scanf("%d", &n);

	if (n < 10)
		printf("%d", n);
	else
		Divide(n);

	return 0;
}

/*
[ 문제 3 ] 양의 정수를 입력받아, 각 자리의 수를 낮은 자릿수부터 차례로 출력하는 프로그램을 작성하시오(나머지 조건은 문제 2와 동일).
*/

#include <stdio.h>
#include <stdlib.h>

void Divide(int n) {
	if (n < 10)
		printf("%d", n);
	else {
		printf("%d\n", n % 10);
		Divide(n / 10);

	}
}

int main() {

	int n, res = 0;
	scanf("%d", &n);

	if (n < 10)
		printf("%d", n);
	else
		Divide(n);

	return 0;
}

/*
[ 문제 4 ] 정수 N ≤ 20을 입력받아 최대값을 구하는 프로그램을 작성하시오.
*/

#include <stdio.h>
#include <stdlib.h>

int max(int n, int x[]) {
	int m;

	if (n == 0)
		return x[0];

	m = max(n - 1, x);
	if (m < x[n])
		return x[n];
	else
		return m;
}

int main() {

	int n, x[20], i, res;
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%d", &x[i]);

	res = max(n - 1, x);

	printf("%d", res);

	return 0;
}

/*
[ 문제 5 ] 원반의 개수 N을 입력받아, 하노이 탑 문제의 수행과정을 예시와 같이 출력하는 프로그램을 작성하시오.
◦ 하노이 탑(towers of Hanoi) 문제
- 세 개의 말뚝: A, B, C
- 초기 상황: 직경이 다른 N > 0개의 원반이 A에 쌓여 있음
- 목표: 모든 원반을 A로부터 C로 옮김
◦ 조건
- 한 번에 말뚝의 가장 위에 있는 한 개의 원반만 이동 가능
- 직경이 큰 원반은 작은 원반 위에 놓일 수 없음
- 남은 말뚝을 보조 말뚝으로 사용 가능
*/

#include <stdio.h>
#include <stdlib.h>

void rHanoi(int n, char from, char aux, char to) {
	if (n == 1)
		printf("%c %c\n", from, to);
	else {
		rHanoi(n - 1, from, to, aux);
		printf("%c %c\n", from, to);
		rHanoi(n - 1, aux, from, to);
	}
}

int main() {

	int n;
	scanf("%d", &n);
	rHanoi(n, 'A', 'B', 'C');

	return 0;
}

/*
[ 문제 6 ] 두 개의 양의 정수를 입력받아, 이 두 정수의 최대공약수(gcd)를 유클리드 호제법으로 계산하여 출력하는 프로그램을 작성하시오.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int gcd(int a, int b) {
	if (b == 0)
		return a;
	else
		return gcd(b, a%b);
}

int main() {

	int a, b, result = 0;

	scanf("%d %d", &a, &b);
	result = gcd(a, b);
	printf("%d", result);

	return 0;
}

/*
[ 문제 7 ] 공백없는 영어 문자열 한 개를 입력받아, 특정 문자가 몇 번 나타나는지 검사하는 프로그램을 작성하시오.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int countletter(char str[], int len, char letter) {
	int cnt = 0, i = 0;

	if (len >= 0) {
		if (str[len - 1] == letter)
			return (1 + countletter(str, len - 1, letter));
		else
			return (countletter(str, len - 1, letter));
	}
	else
		return 0;
}

int main() {

	char str[100], letter;
	int cnt = 0;

	scanf("%s", str);
	getchar();
	scanf("%c", &letter);
	cnt = countletter(str, strlen(str), letter);
	printf("%d", cnt);

	return 0;
}