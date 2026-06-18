#include <stdio.h>
void reverseString(char *s, int sSize) {
  if (s == NULL || sSize <= 1) {
    return;
  }

  char *left_pointer = s;
  char *right_pointer = s + sSize - 1;

  while (left_pointer < right_pointer) {
    char tmp_char = *left_pointer;
    *left_pointer = *right_pointer;
    *right_pointer = tmp_char;

    left_pointer++;
    right_pointer--;
  }
}
