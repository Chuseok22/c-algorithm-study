#include <stdio.h>
#include <_stdlib.h>
int sum_recursion(int n) {
  if (n == 1) {
    return 1;
  } else if (n < 1) {
    fprintf(stderr, "양의 정수 N을 입력하세요\n");
    return EXIT_FAILURE;
  }
  return n + sum_recursion(n - 1);
}

int main(void) {
  int n, result;
  scanf("%d", &n);
  result = sum_recursion(n);
  fprintf(stdout, "%d", result);
}
