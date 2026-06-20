#include <stdio.h>
#include <stdint.h>
#include <mach/mach_time.h>

int main(void) {
  mach_timebase_info_data_t timebase_info;

  // Windows의 QueryPerformanceFrequency()에 대응하는 초기화
  kern_return_t timebase_result = mach_timebase_info(&timebase_info);

  if (timebase_result != KERN_SUCCESS) {
    fprintf(stderr, "타이머 정보를 가져오지 못했습니다.\n");
    return 1;
  }

  // Windows의 QueryPerformanceCounter(&start)에 대응
  uint64_t start_time = mach_absolute_time();

  /*
   * 시간을 측정하고 싶은 작업
   *
   * 실제 과제에서는 아래 반복문 대신
   * 측정할 알고리즘 함수 호출을 넣으면 된다.
   */
  volatile unsigned long long sum = 0;

  // 여기에 함수 작성

  // Windows의 QueryPerformanceCounter(&end)에 대응
  uint64_t end_time = mach_absolute_time();

  uint64_t elapsed_ticks = end_time - start_time;

  /*
   * mach_absolute_time()의 tick을 나노초로 변환
   *
   * elapsed_ticks × numer ÷ denom = nanoseconds
   */
  long double elapsed_nanoseconds =
      (long double) elapsed_ticks
      * (long double) timebase_info.numer
      / (long double) timebase_info.denom;

  long double elapsed_microseconds =
      elapsed_nanoseconds / 1000.0L;

  long double elapsed_milliseconds =
      elapsed_nanoseconds / 1000000.0L;

  long double elapsed_seconds =
      elapsed_nanoseconds / 1000000000.0L;

  printf("result: %llu\n", sum);
  printf("time: %.12Lf sec\n", elapsed_seconds);
  printf("time: %.9Lf ms\n", elapsed_milliseconds);
  printf("time: %.6Lf us\n", elapsed_microseconds);
  printf("time: %.0Lf ns\n", elapsed_nanoseconds);

  return 0;
}
