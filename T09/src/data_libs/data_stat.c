#include "data_stat.h"
#include <math.h>

double max(double *data, int n) {
  if (n <= 0)
    return 0;

  double max_value = data[0];
  for (int i = 1; i < n; i++) {
    if (data[i] > max_value) {
      max_value = data[i];
    }
  }
  return max_value;
}

double min(double *data, int n) {
  if (n <= 0)
    return 0;

  double min_value = data[0];
  for (int i = 1; i < n; i++) {
    if (data[i] < min_value) {
      min_value = data[i];
    }
  }
  return min_value;
}

double mean(double *data, int n) {
  if (n <= 0)
    return 0;

  double sum = 0;
  for (int i = 0; i < n; i++) {
    sum += data[i];
  }
  return sum / n;
}

double variance(double *data, int n) {
  if (n <= 0)
    return 0;

  double mean_value = mean(data, n);
  double sum_sq = 0;

  for (int i = 0; i < n; i++) {
    sum_sq += (data[i] - mean_value) * (data[i] - mean_value);
  }

  return sum_sq / n;
}