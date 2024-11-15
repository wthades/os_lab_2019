#include "sum.h"
#include <stddef.h>  // Добавляем заголовочный файл для size_t

long long Sum(const struct SumArgs *args) {
  long long sum = 0;
  for (int i = args->begin; i < args->end; i++) {
    sum += args->array[i];
  }
  return sum;
}

void *ThreadSum(void *args) {
  struct SumArgs *sum_args = (struct SumArgs *)args;
  long long sum = Sum(sum_args);  // Исправляем возвращаемое значение
  return (void *)(long long)sum;
}