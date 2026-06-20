#include <stdio.h>
/**
 * - disk 가 1 인 경우 destination(C) 으로 이동
 * - disk 가 1이 아닌경우 sub_rod(B) 로 이동
 */
void move_disk(int disk_count, char source_rod, char sub_rod, char destination_rod) {
  if (disk_count == 1) {
    printf("%c %c\n", source_rod, destination_rod);
    return;
  }

  // 최하위 disk 제외 나머지를 sub_rod 로 이동
  move_disk(disk_count - 1, source_rod, destination_rod, sub_rod);

  // 최하위 disk 를 destination_rod 로 이동
  printf("%c %c\n", source_rod, destination_rod);

  // sub_rod 에 있는 disk 를 destination_rod 로 이동
  move_disk(disk_count - 1, sub_rod, source_rod, destination_rod);
}

int main(void) {
  int n;
  scanf("%d", &n);

  move_disk(n, 'A', 'B', 'C');
}
