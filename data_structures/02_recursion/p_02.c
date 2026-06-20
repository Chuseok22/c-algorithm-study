#include <stdio.h>
#include <_stdlib.h>

void print_digits_integer(int n) {
  if (n < 10) {
    fprintf(stdout, "%d\n", n);
    return;
  }

  print_digits_integer(n / 10);

  fprintf(stdout, "%d\n", n % 10);
}

int main(void) {
  int n;
  scanf("%d", &n);
  print_digits_integer(n);
  return EXIT_SUCCESS;
}
