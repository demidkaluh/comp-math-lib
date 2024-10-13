#include "square.h"

double get_discr (sq_equation_t *sq)
{
  double a = sq->a;
  double b = sq->b;
  double c = sq->c;

  return (b * b) - (4 * a * c);
}

int get_sign (double num)
{
  if (num < 0)
    return LESS_ZERO;
  else if (num == 0)
    return ZERO;
  else
    return MORE_ZERO;
}

int get_equation_type (sq_equation_t *sq)
{
  double a = sq->a;
  double b = sq->b;
  double c = sq->c;

  if (a == 0)
  {
    if (b == 0)
    {
      if (c == 0)
        return ZEROCOEFFS;
      else
        return ONLY_C_COEFF;
    }
    else
      return LINEAR;
  }
  else
    return SQUARE;
}

int get_square_equation_type (sq_equation_t *sq)
{
  double d          = get_discr (sq);
  int    discr_sign = get_sign (d);

  switch (discr_sign)
  {
  case (LESS_ZERO):
    return NO_ROOTS;
  case (ZERO):
    return ONE_ROOT;
  case (MORE_ZERO):
    return (TWO_ROOTS);
  }

  return ERROR_EQUATION;
}

void solve_linear (sq_equation_t *sq, roots *r)
{
  double b = sq->b;
  double c = sq->c;

  r->x1 = -c / b;
}

int solve_square (sq_equation_t *sq, roots *r)
{
  double a      = sq->a;
  double b      = sq->b;
  double c      = sq->c;
  double d      = get_discr (sq);
  double root_d = pow (d, 0.5);

  int root_amount = get_square_equation_type (sq);

  switch (root_amount)
  {
  case (ONE_ROOT):
    r->x1 = (-b / 2 * a);
    break;
  case (TWO_ROOTS):
    r->x1 = (-b + root_d) / (2 * a);
    r->x2 = (-b - root_d) / (2 * a);
    break;
  }

  return root_amount;
}

int solve (sq_equation_t *sq, roots *r)
{
  int eq_type = get_equation_type (sq);
  int sq_eq_type;

  switch (eq_type)
  {
  case ZEROCOEFFS:
    return INF_ROOTS;
  case ONLY_C_COEFF:
    return NO_ROOTS;
  case LINEAR:
    solve_linear (sq, r);
    return ONE_ROOT;
  case SQUARE:
    sq_eq_type = solve_square (sq, r);
    return sq_eq_type;
  }

  return ERROR_EQUATION;
}

void print_results (int exit_code, sq_equation_t *sq, roots *r)
{
  printf ("Equation {%f, %f, %f} has ", sq->a, sq->b, sq->c);
  switch (exit_code)
  {
  case NO_ROOTS:
    printf ("no roots\n");
    break;

  case INF_ROOTS:
    printf ("infinite roots\n");
    break;

  case ONE_ROOT:
    printf ("one root : x=%f\n", r->x1);
    break;

  case TWO_ROOTS:
    printf ("two roots : x1=%f x2=%f\n", r->x1, r->x2);
    break;
  default:
    printf ("root amount error\n");
  }
}

void solve_and_print (sq_equation_t *sq, roots *r)
{
  int type = solve (sq, r);
  print_results (type, sq, r);
}

int get_coeffs (sq_equation_t *sq)
{
  int correct = scanf ("%lf %lf %lf", &sq->a, &sq->b, &sq->c);
  if (correct != 3)
  {
    printf ("Error : not enough coeffs\n");
    return get_coeffs (sq);
  }
  return 0;
}

void test ()
{
  sq_equation_t sqs[10] = {
    { 1, -2,  1 },
    { 0, -2,  0 },
    { 1, -2, 53 },
    { 5, -1,  1 },
    { 0,  0,  1 },
    { 1,  0,  0 },
    { 0,  0,  0 },
    { 4,  0,  1 },
    { 2, 15,  2 },
    { 3, -8,  1 },
  };
  roots r;
  for (int i = 0; i < 10; i++)
  {
    solve_and_print (&sqs[i], &r);
  }
}
/*
int main ()
{
  sq_equation_t sq;
  roots         r;

  while (1)
  {
    get_coeffs (&sq);
    solve_and_print (&sq, &r);
  }

  return 0;
}*/
