#include <math.h>
#include <stdio.h>

enum ROOTS
{
  NO_ROOTS,
  INF_ROOTS,
  ONE_ROOT,
  TWO_ROOTS,
  ERROR_ROOTS
};

enum EQUATION_TYPE
{
  ZEROCOEFFS,
  ONLY_C_COEFF,
  LINEAR,
  SQUARE,
  ERROR_EQUATION
};

struct roots
{
  double x1;
  double x2;
} typedef roots;

struct sq_equtation
{
  double a;
  double b;
  double c;
} typedef sq_equation_t;

enum SIGN
{
  LESS_ZERO,
  ZERO,
  MORE_ZERO
};

double get_discr (sq_equation_t *sq);

int  get_sign (double num);
int  get_equation_type (sq_equation_t *sq);
int  get_square_equation_type (sq_equation_t *sq);
void solve_linear (sq_equation_t *sq, roots *r);
int  solve_square (sq_equation_t *sq, roots *r);
int  solve (sq_equation_t *sq, roots *r);
void print_results (int exit_code, sq_equation_t *sq, roots *r);
void solve_and_print (sq_equation_t *sq, roots *r);
int  get_coeffs (sq_equation_t *sq);
void test ();
