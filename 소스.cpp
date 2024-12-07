#include <stdio.h>

int n;
int arr[50][50];

void move_blocks_up() {
	int i, j, zero_index, fusion_index;
	for (i = 0; i < n; i++) {
		zero_index = -2;
		fusion_index = -2;
		for (j = 0; j < n; j++) {
			if (arr[j][i] == 0) {
				if (zero_index == -2)
					zero_index = j;
				else
					continue;
			}
			else {
				if (zero_index == -2)
					zero_index = 1;
				else {
					if (fusion_index == zero_index - 1) {
						arr[zero_index][i] == arr[j][i];
						arr[j][i] = 0;
						zero_index++;
					}
					else {
						if (zero_index == 0) {
							arr[zero_index][i] == arr[j][i];
							arr[j][i];
							zero_index++;
						}
						else if (arr[zero_index - 1][i] == arr[j][i]) {
							arr[zero_index - 1][i] *= 2;
							arr[j][i] = 0;
							fusion_index = zero_index - 1;
						}
						else {
							if (zero_index != j) {
								arr[zero_index][i] = arr[j][i];
								arr[j][i] = 0;
							}
							zero_index++;
						}
					}
				}
			}
		}
	}
}

void transaction() {
	int i, j, a, b, sub;
	for (i = 0; i < 2 * n - 1; i++)
		for (j = 0; j < (i + 1) / 2; j++) {
			a = j;
			b = i - j;
			if ((a < 0) || (a >= n) || (b < 0) || (b >= n))
				continue;
			sub = arr[a][b];
			arr[a][b] = arr[b][a];
			arr[b][a] = sub;
		}
}

void up_down_change() {
	int i, j, a, b, sub;
	for (i = 0; i < n; i++)
		for (j = 0; j < n / 2; j++) {
			a = j;
			b = (n - 1) - j;
			sub = arr[a][i];
			arr[a][i] = arr[b][i];
			arr[b][i] = sub;
		}
}

void move_blocks(int way) {
	switch (way)
	{
	case 0:
		move_blocks_up();
		break;
	case 1:
		up_down_change();
		move_blocks_up();
		up_down_change();
		break;
	case 2:
		transaction();
		move_blocks_up();
		transaction();
		break;
	case 3:
		transaction();
		up_down_change();
		move_blocks_up();
		up_down_change();
		transaction();
		break;
	default:
		break;
	}
}

void copy_array(int sub_arr[][50], int isCopy) {
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
			if (isCopy)
				sub_arr[i][j] = arr[i][j];
			else
				arr[i][j] = sub_arr[i][j];
		}
}

int dfs(int depth, int now_way) {
	int ans = 0, i, j;
	int sub_arr[50][50];
	if (depth == 5) {
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (ans < arr[i][j])
					ans = arr[i][j];
		return ans;
	}
	move_blocks(now_way);
	copy_array(sub_arr, 1);
	for (i = 0; i < 4; i++) {
		ans = ans > dfs(depth + 1, i) ? ans : dfs(depth + 1, i);
		copy_array(sub_arr, 0);
	}
	return ans;
}

int main() {

	int ans = 0, i, j;
	int sub_arr[50][50] = { 0 };
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			scanf("%d", &arr[i][j]);
	copy_array(sub_arr, 1);
	for (i = 0; i < 4; i++) {
		ans = ans > dfs(0, i) ? ans : dfs(0, i);
		copy_array(sub_arr, 0);
		if (i == 3)
			printf("%d", ans);
	}

	return 0;
}