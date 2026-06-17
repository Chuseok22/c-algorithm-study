#include <stdio.h>

int sum(int x, int y);

int main(void) {
  int n = 0, result = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    result = sum(result, i);
  }
  printf("%d", result);
  return 0;
}

int sum(int x, int y) {
  return x + y;
}
