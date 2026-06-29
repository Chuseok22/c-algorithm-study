#include <stddef.h>

struct ListNode {
  int val;
  struct ListNode *next;
};

int getDecimalValue(struct ListNode *head) {
  int size = 1, result = 0, base = 1;
  struct ListNode *node = head;

  while (node->next != NULL) {
    size++;
    base *= 2;
    node = node->next;
  }

  for (int i = 0; i < size; i++) {
    result = head->val * base + result;
    head = head->next;
    base /= 2;
  }

  return result;
}
