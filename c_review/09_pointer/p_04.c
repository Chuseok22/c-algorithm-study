#include <stdio.h>

void swap(int *pointer1, int *pointer2) {
  int tmp;
  tmp = *pointer1;
  *pointer1 = *pointer2;
  *pointer2 = tmp;
}

int main(void) {
  int array[3];
  int *array_pointer1 = array, *array_pointer2 = array;

  for (array_pointer1 = array; array_pointer1 < array + 3; array_pointer1++) {
    scanf("%d", array_pointer1);
  }

  for (array_pointer1 = array; array_pointer1 < array + 3; array_pointer1++) {
    for (array_pointer2 = array_pointer1; array_pointer2 < array + 3; array_pointer2++) {
      if (*array_pointer1 > *array_pointer2) {
        swap(array_pointer1, array_pointer2);
      }
    }
  }

  for (array_pointer1 = array; array_pointer1 < array + 3; array_pointer1++) {
    printf("%d ", *array_pointer1);
  }
}
