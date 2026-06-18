#include <stdio.h>
int fib(int n) {
  // 1 1 2 3 5
  if (n == 0) {
    return 0;
  }
  if (n == 1) {
    return 1;
  }
  return fib(n - 1) + fib(n - 2);
}

int main(void) {
  int n;
  scanf("%d", &n);
  fprintf(stdout, "%d", fib(n));
}
