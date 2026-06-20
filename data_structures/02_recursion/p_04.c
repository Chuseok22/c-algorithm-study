#include <stdio.h>
#include <stdlib.h>

int find_max_integer(int *integer_array, int number_count) {
  if (number_count == 1) {
    return integer_array[0];
  }

  int previous_maximum = find_max_integer(integer_array, number_count - 1);

  int current_number = integer_array[number_count - 1];
  if (previous_maximum < current_number) {
    return current_number;
  }
  return previous_maximum;
}

int main(void) {
  int n, result;
  scanf("%d", &n);

  int integer_array[20];
  for (int i = 0; i < n; i++) {
    scanf("%d", &integer_array[i]);
  }
  result = find_max_integer(integer_array, n);
  printf("%d", result);

  return EXIT_SUCCESS;
}
