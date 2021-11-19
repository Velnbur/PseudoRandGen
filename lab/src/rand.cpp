#include "rand.h"
#include <math.h>
#include <time.h>

#if DEBUG
#include <stdio.h>
#endif // DEBUG

static const int M_MOD = 16411;

enum PSEUDO_RAND_METHOD {
  LINEAR = 1,
  SQUARE,
  FIBB_NUMS,
  REVERSE,
  UNION,
  THREE_SIGMA,
  POLLAR_COOR,
  CORRELATION,
  EXPONENTIAL,
  ARENS,
};

typedef double (*rand_func_t)(unsigned int &);

/*
** Find inversed by mod number
**
** @param num Number to inverse
**        m Mod
** @return ineversed 'num' by 'm'
*/
static int inv_mod(int num, int m) {
  int res = 1;
  int n = m - 2;
  while (n) {
    if (n % 2)
      res = (res * num) % m;
    n = n >> 1;
    num = (num * num) % m;
  }
  return res;
}

/*
** Generate 'nums' of pseudo generated numbers and fill buff for
** interval [0; 1] - equally
**
** @param buff Buff size of 10 that will be filled
**        nums Amount of number that will be generated
**        f Function that generates new pseudo random numbers
*/
static void fill_buff(unsigned int buff[10], int nums, rand_func_t f) {
  unsigned int x = time(0) % M_MOD - 1;

  for (int i = 0; i < nums; ++i) {
    double u = f(x);
#if DEBUG
    printf("%f\n", u);
    fflush(stdout);
#endif
    buff[static_cast<int>(u * 10)]++;
  }
}

/*
** Generate 'nums' of pseudo generated numbers and fill buff for
** interval [-3; 3] - normal
**
** @param buff Buff size of 10 that will be filled
**        nums Amount of number that will be generated
**        f Function that generates new pseudo random numbers
*/
static void fill_normal_buff(unsigned int buff[10], int nums, rand_func_t f) {
  unsigned int x = time(0) % M_MOD;

  for (int i = 0; i < nums; ++i) {
    double u = f(x);
#if DEBUG
    printf("%f\n", u);
    fflush(stdout);
#endif
    int res = static_cast<int>(((u + 3)) / 6 * 10);
    if (res > 9)
      res = 9;
    else if (res < 0)
      res = 0;
    buff[res]++;
  }
}

/*
** Generate 'nums' of pseudo generated numbers and fill buff for
** interval [0; 100] - other methods
**
** @param buff Buff size of 10 that will be filled
**        nums Amount of numbers that will be generated
**        f Function that generates new pseudo random numbers
*/
static void fill_other_buff(unsigned int buff[10], int nums, rand_func_t f) {
  unsigned int x = time(0) % M_MOD;

  for (int i = 0; i < nums; ++i) {
    double u = f(x);
#if DEBUG
    printf("%f\n", u);
    fflush(stdout);
#endif
    if (u > 100.0 || u < 0) {
      continue;
    }
    buff[static_cast<int>(u / 10)]++;
  }
}

/*<-----------PSEUDO_RANDOM_GENERATORS------------->*/

/*
** Family of pseudo random generating functions
**
** @param x Xn after and of the fucntion will be X(n+1)
** @return New pseudo random generated number
*/

/*<---EQUAL_METHODS--->*/

/* Linear Coheent Method */
static double linear_cog(unsigned int &x) {
  const int a = 17;
  const int c = 19;

  x = (a * x + c) % M_MOD;

  return static_cast<double>(x) / M_MOD;
}

/* Square Coherent Method */
static double square_cog(unsigned int &x) {
  const int a = 17;
  const int c = 19;
  const unsigned long d = 4;
  unsigned long tmp = x;

  x = (d * tmp * tmp + (a * tmp) + c) % M_MOD;
#if DEBUG
  printf("%u\n", x);
#endif

  return static_cast<double>(x) / M_MOD;
}

/* Fibbonachi Congruent Method */
static double fibb_nums(unsigned int &x) {
  static int a = 6765;
  int tmp;

  tmp = x;
  x = (a + x) % M_MOD;
  a = tmp;

  return static_cast<double>(x) / M_MOD;
}

/* Inverse Congruent Method */
static double reverse_cog(unsigned int &x) {
  const int a = 17;
  const int c = 19;

  x = (a * inv_mod(x, M_MOD) + c) % M_MOD;

  return static_cast<double>(x) / M_MOD;
}

/*
** Union Congruent Method
**
** uses union of Fibbonachi Numbers and Linear Coherent Method
*/
static double union_cog(unsigned int &x) {
  unsigned int y = x, z = x;

  fibb_nums(y);
  linear_cog(z);
  x = (y + (M_MOD - z) % M_MOD) % M_MOD;

  return static_cast<double>(x) / M_MOD;
}

/*<---NORMAL_METHODS--->*/

/* Three Sigma Rule Method */
static double three_sigma(unsigned int &x) {
  double sum = 0;

  for (int i = 0; i < 12; ++i)
    sum += fibb_nums(x);

  return sum - 6;
}

/* Polar Coordinates Method */
static double polar_coor(unsigned int &x) {
  double s, v1, v2;

  do {
    v1 = 2 * linear_cog(x) - 1;
    v2 = 2 * linear_cog(x) - 1;

    s = (v1 * v1 + v2 * v2);
  } while (s >= 1);

  return v1 * sqrt((-2 * log(s)) / s);
}

/* Correlation Method */
static double correlation(unsigned int &x) {
  double u, v, y2, y;

  do {
    u = linear_cog(x);
    v = linear_cog(x);

    // sqrt(8/e) = 1.715527
    y = 1.715527 * (v - 0.5) / u;
    y2 = y * y;

    // 4*e^(1/4) = 5.136101
    if (y2 <= (5 - 5.136101 * u))
      break;
    // 4*e^(-1.35) = 1.036961
    if (y2 < (1.036961 / u + 1.4))
      break;
  } while (y2 > (-4 * log(u)));
  return y;
}

/* <--OTHER_METHODS--> */

/* Exponantial Log Method */
static double exponential(unsigned int &x) {
  double u = fibb_nums(x);
  return -31 * log(u);
}

/* Arens Method */
static double arens(unsigned int &x) {
  const int a = 32;
  double u, y, z, v;

  do {
    u = union_cog(x);
    y = tan(M_PI * u);
    z = sqrt(2 * a - 1) * y + a - 1;

    if (z > 0)
      break;
    v = linear_cog(x);
  } while (v > ((1 + y * y) *
                exp((a - 1) * log(z / (a - 1)) - sqrt(2 * a - 1) * y)));
  return z;
}

/*
** Find the right fucntion to generate pseudo random numbers for the method
**
** @param _method Number of generationg method
** @return pointer to function that will generate numbers for that method
**         if there is no such method -> retrun nullptr
*/
static rand_func_t choose_method(int _method) {
  PSEUDO_RAND_METHOD method = static_cast<PSEUDO_RAND_METHOD>(_method);

  switch (method) {
  case LINEAR:
    return linear_cog;
  case SQUARE:
    return square_cog;
  case REVERSE:
    return reverse_cog;
  case FIBB_NUMS:
    return fibb_nums;
  case UNION:
    return union_cog;
  case THREE_SIGMA:
    return three_sigma;
  case POLLAR_COOR:
    return polar_coor;
  case CORRELATION:
    return correlation;
  case EXPONENTIAL:
    return exponential;
  case ARENS:
    return arens;
  }
  return nullptr;
}

int get_rates(int method, int num_c, double *rates) {
  rand_func_t f = choose_method(method);
  if (!f)
    return -1;

  unsigned int buff[10] = {};
  if (method <= 5)
    fill_buff(buff, num_c, f);
  else if (method <= 8)
    fill_normal_buff(buff, num_c, f);
  else
    fill_other_buff(buff, num_c, f);

  for (int i = 0; i < 10; ++i)
    rates[i] = static_cast<double>(buff[i]) / num_c;
  return 0;
}
