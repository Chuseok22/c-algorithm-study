#include <stdlib.h>
/**
* Note: The returned array must be malloced, assume caller calls free().
 */
int *runningSum(int *nums, int numsSize, int *returnSize) {
  int *result_array = malloc(sizeof(*result_array) * numsSize);
  if (result_array == NULL) {
    return NULL;
  }

  *result_array = *nums;

  for (int index = 1; index < numsSize; index++) {
    *(result_array + index) = *(result_array + index - 1) + *(nums + index);
  }
  *returnSize = numsSize;
  return result_array;
}
