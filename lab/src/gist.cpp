//
// Module for drawing diagrams for each method
//

#include "gist.h"
#include <stdio.h>

static void draw_line(int lenght, char sym) {
  for (int j = 0; j < lenght; ++j) {
    putc(sym, stdout);
  }
  putc('\n', stdout);
}

static void draw_equal_gist(double *rates) {
  for (int i = 0; i < 10; ++i) {
    if (i == 9)
      printf("[0.%d; 1.0]\t%0.2f\t", i, rates[i]);
    else
      printf("[0.%d; 0.%d]\t%0.2f\t", i, i + 1, rates[i]);
    if (rates[i] > 0 && rates[i] < 0.01)
      draw_line(1, '.');
    else
      draw_line(static_cast<int>(rates[i] * 100), '#');
  }
}

static void draw_normal_gist(double *rates) {
  double diap = -3.0;

  for (int i = 0; i < 10; ++i) {
    printf("[%+.1f; %+.1f]\t%0.2f\t", diap, diap + 0.6, rates[i]);

    diap += 0.6;
    if (rates[i] > 0 && rates[i] < 0.01)
      draw_line(1, '.');
    else
      draw_line(static_cast<int>(rates[i] * 100), '#');
  }
}

static void draw_other_gist(double *rates) {
  for (int i = 0; i < 10; ++i) {

    if (i == 0)
      printf("[ %d; %d]\t%0.2f\t", i * 10, (i + 1) * 10, rates[i]);
    else
      printf("[%d; %d]\t%0.2f\t", i * 10, (i + 1) * 10, rates[i]);

    if (rates[i] > 0 && rates[i] < 0.01)
      draw_line(1, '.');
    else
      draw_line(static_cast<int>(rates[i] * 100), '#');
  }
}

void draw_gist(double *rates, int method) {
    if (method <= 5)
      draw_equal_gist(rates);
    else if (method <= 8)
      draw_normal_gist(rates);
    else
      draw_other_gist(rates);
}
