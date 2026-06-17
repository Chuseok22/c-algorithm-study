#include <stdio.h>
int main(void) {
  int n = 0;
  scanf("%d", &n);

  int integer_array[50];
  int *integer_pointer = integer_array;

  for (integer_pointer; integer_pointer < integer_array + n; integer_pointer++) {
    scanf("%d", integer_pointer);
  }
  integer_pointer = integer_array;
  while (integer_pointer < integer_array + n) {
    if (*integer_pointer == 0) {
      break;
    }
    integer_pointer++;
  }
  printf("%d", integer_pointer - integer_array);
}
