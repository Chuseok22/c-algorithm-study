#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  struct Node *prev;
  int value;
  struct Node *next;
} Node;

typedef struct {
  Node *header;
  Node *trailer;
  int size;
} MyLinkedList;

Node *createNode(int value) {
  Node *node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "node 메모리 할당 실패");
    exit(EXIT_FAILURE);
  }
  node->value = value;
  node->prev = NULL;
  node->next = NULL;
  return node;
}

MyLinkedList *myLinkedListCreate(void) {
  MyLinkedList *list = malloc(sizeof(*list));
  if (list == NULL) {
    fprintf(stderr, "list메모리 할당 실패");
    exit(EXIT_FAILURE);
  }

  list->header = createNode(0);
  list->trailer = createNode(0);

  list->header->next = list->trailer;
  list->trailer->prev = list->header;
  list->size = 0;

  return list;
}

Node *getNode(MyLinkedList *obj, int index) {
  if (index < 0 || index >= obj->size) {
    return NULL;
  }
  Node *currentNode = obj->header->next;
  for (int i = 0; i < index; i++) {
    currentNode = currentNode->next;
  }
  return currentNode;
}

int myLinkedListGet(MyLinkedList *obj, int index) {
  Node *node = getNode(obj, index);
  if (node == NULL) {
    return -1;
  }
  return node->value;
}

void myLinkedListAddAtHead(MyLinkedList *obj, int val) {
  Node *newNode = createNode(val);
  Node *nextNode = obj->header->next;

  obj->header->next = newNode;

  newNode->prev = obj->header;
  newNode->next = nextNode;

  nextNode->prev = newNode;

  obj->size++;
}

void myLinkedListAddAtTail(MyLinkedList *obj, int val) {
  Node *newNode = createNode(val);
  Node *prevNode = obj->trailer->prev;

  obj->trailer->prev = newNode;

  newNode->prev = prevNode;
  newNode->next = obj->trailer;

  prevNode->next = newNode;

  obj->size++;
}

void myLinkedListAddAtIndex(MyLinkedList *obj, int index, int val) {
  Node *nextNode;
  // index 가 size 보다 큰 경우
  if (index < 0 || index > obj->size) {
    return;
  }
  if (index == obj->size) {
    nextNode = obj->trailer;
  } else {
    nextNode = getNode(obj, index);
  }

  if (nextNode == NULL) {
    return;
  }

  Node *prevNode = nextNode->prev;
  Node *newNode = createNode(val);

  newNode->prev = nextNode->prev;
  newNode->next = nextNode;

  prevNode->next = newNode;

  nextNode->prev = newNode;

  obj->size++;
}

void freeNode(Node *node) {
  free(node);
}

void myLinkedListDeleteAtIndex(MyLinkedList *obj, int index) {
  if (index < 0 || index >= obj->size) {
    return;
  }
  Node *targetNode = getNode(obj, index);
  if (targetNode == NULL) {
    return;
  }
  Node *nextNode = targetNode->next;
  Node *prevNode = targetNode->prev;

  prevNode->next = nextNode;
  nextNode->prev = prevNode;

  obj->size--;

  freeNode(targetNode);
}

void myLinkedListFree(MyLinkedList *obj) {
  Node *currentNode = obj->header;
  while (currentNode != NULL) {
    Node *nextNode = currentNode->next;
    freeNode(currentNode);
    currentNode = nextNode;
  }
  free(obj);
}

/**
 * Your MyLinkedList struct will be instantiated and called as such:
 * MyLinkedList* obj = myLinkedListCreate();
 * int param_1 = myLinkedListGet(obj, index);

 * myLinkedListAddAtHead(obj, val);

 * myLinkedListAddAtTail(obj, val);

 * myLinkedListAddAtIndex(obj, index, val);

 * myLinkedListDeleteAtIndex(obj, index);

 * myLinkedListFree(obj);
*/
