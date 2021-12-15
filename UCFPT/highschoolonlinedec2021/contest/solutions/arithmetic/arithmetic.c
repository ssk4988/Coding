#include <stdio.h>

int main() {
	int testCases;
	scanf("%d", &testCases);

	for(int i = 0; i < testCases; i++) {
		int n, s;
		scanf("%d %d", &n, &s);

		if((s * 2) % n != 0) {
			printf("IMPOSSIBLE\n");
		}
		else if((s * 2 / n) % 2 == 0) {
			int res = s / n;
			for(int i = 0; i < n; i++) {
				printf("%d ", res);
			}
			printf("\n");
		}
		else {
			int first = (s * 2 / n - (n - 1)) / 2;
			for(int i = 0; i < n; i++) {
				printf("%d ", i + first);
			}
			printf("\n");
		}

	}
	return 0;
}
