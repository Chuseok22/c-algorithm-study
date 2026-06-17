#include <stdio.h>

typedef struct Student {
  char name[10];
  int score;
} Student;

#define STUDENT_COUNT 5

Student *select_min(Student *student_array) {
  Student *min_student_pointer = student_array;
  Student *current_student_pointer = NULL;

  for (current_student_pointer = student_array; current_student_pointer < student_array + STUDENT_COUNT; current_student_pointer++) {
    if (current_student_pointer->score < min_student_pointer->score) {
      min_student_pointer = current_student_pointer;
    }
  }

  return min_student_pointer;
}

int main(void) {
  Student student[STUDENT_COUNT];
  Student *student_pointer = student;

  for (student_pointer = student; student_pointer < student + STUDENT_COUNT; student_pointer++) {
    scanf("%s %d", student_pointer->name, &student_pointer->score);
    if (student_pointer->score < 0 || student_pointer->score > 100) {
      fprintf(stderr, "점수는 0과 100사이의 정수만 가능");
      return 1;
    }
  }
  Student *min_student_pointer = select_min(student);
  fprintf(stdout, "%s %d", min_student_pointer->name, min_student_pointer->score);
}
