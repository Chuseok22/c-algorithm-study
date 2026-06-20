#include <stdio.h>
void print_integer_digits(int n) {
  if (n <= 0) {
    return;
  }
  printf("%d\n", n % 10);

  print_integer_digits(n / 10);
}

int main(void) {
  int n;
  scanf("%d", &n);
  print_integer_digits(n);
}
