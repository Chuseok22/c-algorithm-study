#include <stdio.h>
#include <stdlib.h>

int search(int *nums, int numsSize, int target) {
  int first_index = 0, last_index = numsSize - 1;

  while (first_index <= last_index) {
    int index = (first_index + last_index) / 2;

    if (nums[index] == target) {
      return index;
    }

    if (nums[index] > target) {
      last_index = index - 1;
    } else if (nums[index] < target) {
      first_index = index + 1;
    }
  }
  return -1;
}

int main(void) {
  int size;
  printf("배열의 크기: ");
  scanf("%d", &size);

  int *integer_array_pointer = malloc(sizeof(*integer_array_pointer) * size);
  if (integer_array_pointer == NULL) {
    fprintf(stderr, "메모리 동적할당 실패");
    return EXIT_FAILURE;
  }
  printf("배열을 입력하세요\n");
  for (int i = 0; i < size; i++) {
    scanf("%d", &integer_array_pointer[i]);
  }

  int target;
  printf("타켓 number: ");
  scanf("%d", &target);

  int result = search(integer_array_pointer, size, target);

  if (result == -1) {
    fprintf(stdout, "찾을 수 없음");
  }

  fprintf(stdout, "결과: %d", result);

  free(integer_array_pointer);

  return EXIT_SUCCESS;
}
