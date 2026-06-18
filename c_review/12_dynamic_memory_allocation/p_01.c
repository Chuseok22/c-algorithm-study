#include <stdio.h>
#include <stdlib.h>
int main(void) {
  int N, sum = 0;
  scanf("%d", &N);
  int *int_array = malloc(sizeof(*int_array) * N);

  if (int_array == NULL) {
    fprintf(stderr, "메모리 할당 실패");
    return EXIT_FAILURE;
  }

  for (int *current_pointer = int_array; current_pointer < int_array + N; current_pointer++) {
    scanf("%d", current_pointer);
    sum += *current_pointer;
  }
  printf("%d", sum);
  free(int_array);
}
