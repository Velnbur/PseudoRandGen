#include "gist.h"
#include "rand.h"
#include <stdio.h>

#define BUFF_SIZE 10
#define WRONG_INPUT_MESS "You must enter nhumber from 1 to 10\n"
#define GREET_MESS                                                             \
  "This program generates pseudo random numbers\n"                             \
  "with different methods and draws gistrogram of rates\n"                     \
  "of numbers apearing in each scope; \n"                                      \
  "\n Babula Kyrylo K-21 2021\n"
#define METHODS_MESS "1. Linear Coherent method\n" \
  "2. Square Coherent method\n" \
  "3. Fibbonachi Nums method\n" \
  "4. Reverse Coherent method\n" \
  "5. Union method\n" \
  "6. \"Three sigma\" rule\n" \
  "7. \"Polar coordinates\" method\n" \
  "8. Correlation method\n" \
  "9. Exponential method\n" \
  "10. Aren's method"
#define ENTER_MESS "Enter number from 1 to 10;\n"
#define UNDEFINED_MESS "Sorry there is still no such method!;\n"

int main() {
  double rates[BUFF_SIZE] = {};
#if DEBUG
  int numbers_c = 10;
#else
  int numbers_c = 10'000'000;
#endif


  puts(GREET_MESS);
  puts(METHODS_MESS);
  for (;;) {
    puts(ENTER_MESS);

    int method;
    int bytes = scanf("%d", &method);
    if (method < 0 || method > 10 || bytes > 4) {
      puts(WRONG_INPUT_MESS);
      return -1;
    }
    if(method == 0)
      return 0;

    int res = get_rates(method, numbers_c, rates);
    if (res) {
      puts(UNDEFINED_MESS);
      return -2;
    }

    draw_gist(rates, method);
  }
  return 0;
}
