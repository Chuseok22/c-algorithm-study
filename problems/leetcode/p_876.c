#include <stddef.h>

struct ListNode {
  int val;
  struct ListNode *next;
};

// struct ListNode *middleNode(struct ListNode *head) {
//   int size = 0;
//   struct ListNode *currentNode = head;
//
//   while (currentNode != NULL) {
//     size++;
//     currentNode = currentNode->next;
//   }
//
//   int middleIndex = size / 2;
//   for (int i = 0; i < middleIndex; i++) {
//     head = head->next;
//   }
//   return head;
// }

struct ListNode *middleNode(struct ListNode *head) {
  struct ListNode *fast_node = head;
  struct ListNode *slow_node = head;

  while (fast_node != NULL && fast_node->next != NULL) {
    slow_node = slow_node->next;
    fast_node = fast_node->next->next;
  }

  return slow_node;
}
