#include <stdlib.h>
/**
* Note: The returned array must be malloced, assume caller calls free().
 */
int *getConcatenation(int *nums, int numsSize, int *returnSize) {
  *returnSize = numsSize * 2;

  int *result_array = malloc(sizeof(*result_array) * numsSize * 2);

  if (result_array == NULL) {
    return NULL;
  }

  for (int index = 0; index < numsSize; index++) {
    *(result_array + index) = *(nums + index);
    *(result_array + numsSize + index) = *(nums + index);
  }

  return result_array;
}
