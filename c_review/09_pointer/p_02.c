#include <stdio.h>
int main(void) {
  char ch[21];
  char *pch = ch;
  scanf("%s", ch);

  while (*pch != '#') {
    pch++;
  }

  while (pch > ch) {
    pch--;
    printf("%c", *pch);
  }
}
