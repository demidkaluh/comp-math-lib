#include "MyMatrix.h"
#include "container_cout.h"
#include "square.h"

/*
 Здесь реализован класс матриц Matrix.
Пока матрицы умеют складываться (+,+=), умножаться (*, *=), транспонироваться
и даже(!) возводиться в степень. (UPD : они уже много чего умеют)
 Есть 3 конструктора :
 Matrix() - матрица ранга 0.
 Matrix(int n) - единичная матрица ранга n.
 Matrix(vector<vector<double>> data) - делает из поданного вектора векторов
 хорошую матрицу.
 Можно вывести через cout. В целом всё.
*/

namespace MyMatrix
{
class Matrix
{
private:
  std::vector<std::vector<double> > _data = {};

public:
  // Просто какая-то пустая матрица нулевой размерности
  Matrix () {}

  // Нулевая матрицы NxM
  Matrix (int n, int m)
  {
    std::vector<double> curr_row = {};
    for (size_t i = 0; i < n; i++)
    {
      for (size_t j = 0; j < m; j++)
      {
        curr_row.push_back (0);
      }

      _data.push_back (curr_row);
      curr_row = {};
    }
  }

  // Единичная матрица NxN
  Matrix (int n)
  {
    std::vector<double> curr_row = {};
    for (size_t i = 0; i < n; i++)
    {
      for (size_t j = 0; j < n; j++)
      {
        curr_row.push_back (0);
      }
      _data.push_back (curr_row);
      curr_row = {};
    }

    for (size_t i = 0; i < n; i++)
      _data[i][i] = 1;
  }

  Matrix (std::vector<std::vector<double> > data)
  {
    int columnSize = data[0].size ();
    for (size_t i = 1; i < data.size (); i++)
    {
      if (data[i].size () != columnSize)
      {
        std::cout << "Error : Invalid data was input in matrix constructor - "
                     "columns has not the same length\n";
        exit (1);
      }
    }

    _data = data;
  }

  int  getRowLen () const { return _data.size (); }
  int  getColumnLen () const { return _data[0].size (); }
  bool isSquare () const { return getRowLen () == getColumnLen (); }

  bool checkRows (Matrix &m) const { return (getRowLen () == m.getRowLen ()); }

  bool checkColumns (Matrix &m) const
  {
    return (getColumnLen () == m.getColumnLen ());
  }

  void checkSizes (Matrix &m) const
  {
    if (!(checkRows (m) and checkColumns (m)))
    {
      std::cout << "Error : Inequal dimensions\n";
      exit (1);
    }
  }

  double getElem (unsigned int r, unsigned int c) const
  {
    if ((r >= getRowLen ()) or (c >= getColumnLen ()))
    {
      std::cout << "Error : incorrect reference to the element of matrix\n";
      exit (1);
    }
    return _data[r][c];
  };

  void setElem (unsigned int r, unsigned int c, double val)
  {
    _data[r][c] = val;
  }
  void addRow (std::vector<double> row) { _data.push_back (row); }

  Matrix &operator+= (Matrix m)
  {
    checkSizes (m);

    for (size_t i = 0; i < getRowLen (); i++)
      for (size_t j = 0; j < getColumnLen (); j++)
        this->_data[i][j] += m.getElem (i, j);

    return *this;
  }

  friend Matrix operator+ (Matrix m1, Matrix m2)
  {
    m1.checkSizes (m2);
    Matrix tmp_m = m1;
    tmp_m += m2;

    return tmp_m;
  }

  Matrix &operator*= (Matrix m)
  {
    if (this->getColumnLen () != m.getRowLen ())
    {
      std::cout << "Error : inequal dimensions for multiplication\n";
      exit (1);
    }

    Matrix m_copy = *this;
    _data         = {};

    std::vector<double> curr_row = {};
    for (size_t i = 0; i < m_copy.getRowLen (); i++)
    {
      for (size_t j = 0; j < m.getColumnLen (); j++)
        curr_row.push_back (0);

      _data.push_back (curr_row);
      curr_row = {};
    }

    for (size_t i = 0; i < getRowLen (); i++)
      for (size_t j = 0; j < getColumnLen (); j++)
        for (size_t k = 0; k < m_copy.getColumnLen (); k++)
          this->_data[i][j] += m_copy.getElem (i, k) * m.getElem (k, j);

    return *this;
  }

  Matrix &operator*= (double num)
  {
    for (size_t i = 0; i < getRowLen (); i++)
    {
      for (size_t j = 0; j < getColumnLen (); j++)
      {
        _data[i][j] *= num;
      }
    }

    return *this;
  }

  friend Matrix operator* (Matrix m1, Matrix m2)
  {
    if (m1.getColumnLen () != m2.getRowLen ())
    {
      std::cout << "Error : inequal dimensions for multiplication\n";
      exit (1);
    }
    Matrix tmp_m = m1;
    tmp_m *= m2;

    return tmp_m;
  }

  friend std::vector<double> operator* (Matrix m1, std::vector<double> v)
  {
    Matrix m2 (v.size (), 1);

    for (int i = 0; i < v.size (); i++)
    {
      m2.setElem (i, 0, v[i]);
    }

    if (m1.getColumnLen () != m2.getRowLen ())
    {
      std::cout << "Error : inequal dimensions for multiplication\n";
      exit (1);
    }
    Matrix tmp_m = m1;
    tmp_m *= m2;

    std::vector<double> res;

    for (int i = 0; i < tmp_m.getRowLen (); i++)
    {
      res.push_back (tmp_m.getElem (i, 0));
    }
    return res;
  }

  friend Matrix operator* (double num, Matrix m)
  {
    Matrix tmp_m = m;
    tmp_m *= num;

    return tmp_m;
  }

  friend Matrix operator* (Matrix m, double num) { return num * m; }

  Matrix powm (unsigned int n)
  {
    if (!isSquare ())
    {
      std::cout
          << "Error : only square matrix can be multiplicated on itself\n";
      exit (1);
    }

    Matrix res (getRowLen ());

    for (int i = 0; i < n; i++)
      res *= *this;

    return res;
  }

  double trace () const
  {
    if (!isSquare ())
    {
      std::cout << "Error : only square matrix has trace\n";
      exit (1);
    }

    double res = 0;

    for (size_t i = 0; i < getRowLen (); i++)
    {
      res += _data[i][i];
    }

    return res;
  }

  friend Matrix transpose (Matrix m)
  {
    Matrix m_copy;

    std::vector<double> curr_row = {};

    for (size_t j = 0; j < m.getColumnLen (); j++)
    {
      for (size_t i = 0; i < m.getRowLen (); i++)
        curr_row.push_back (0);

      m_copy._data.push_back (curr_row);
      curr_row = {};
    }

    for (size_t i = 0; i < m.getRowLen (); i++)
    {
      for (size_t j = 0; j < m.getColumnLen (); j++)
        m_copy.setElem (j, i, m.getElem (i, j));
    }

    return m_copy;
  }

  // определитель, ищем по определению со сложностью O(n!)
  friend double det (Matrix m)
  {
    if (!(m.isSquare ()))
    {
      std::cout << "Error : det() requires square matrix\n";
      exit (1);
    }

    if (m.getRowLen () == 2)
    {
      return m.getElem (0, 0) * m.getElem (1, 1)
             - m.getElem (0, 1) * m.getElem (1, 0);
    }

    double res = 0;
    Matrix minor (m.getRowLen () - 1, m.getRowLen () - 1);

    for (int i = 0; i < m.getRowLen (); i++)
    {
      for (int j = 1; j < m.getRowLen (); j++)
      {
        for (int k = 0; k < m.getColumnLen (); k++)
        {
          // std::cout << minor;
          if (k < i)
            minor.setElem (j - 1, k, m.getElem (j, k));
          else if (k > i)
            minor.setElem (j - 1, k - 1, m.getElem (j, k));
        }
      }

      res += m.getElem (0, i) * pow (-1, i) * det (minor);
    }

    return res;
  }

  // пока только 2x2
  friend std::vector<double> eigenvalues (Matrix m)
  {
    if (!m.isSquare ())
    {
      std::cout << "Error : eigenvalues() requres square matrix\n";
      exit (1);
    }

    if (m.getRowLen () != 2)
    {
      std::cout << "Error : eigenvalues() calculates only 2x2 matrixes\n";
      exit (1);
    }

    std::vector<double> res = {};
    //(l - a11)(l - a22) - a12*a21; l*l - l*a22 -l*a11 + a11*a22 - a12*a21
    sq_equation_t det;
    det.a = 1;
    det.b = -(m.getElem (0, 0) + m.getElem (1, 1));
    det.c = m.getElem (0, 0) * m.getElem (1, 1)
            - m.getElem (0, 1) * m.getElem (1, 0);

    roots *r;

    int exit_code = solve (&det, r);
    switch (exit_code)
    {
    case NO_ROOTS:
      break;

    case INF_ROOTS:
      break;

    case ONE_ROOT:
      res.push_back (r->x1);
      break;

    case TWO_ROOTS:
      res.push_back (r->x1);
      res.push_back (r->x2);
      break;

    default:
      printf ("Error : eigenvalues root amount error\n");
    }

    return res;
  }

  // Обратная (пока неправильно)                     ???????????
  friend Matrix reverse (Matrix m) { return (1 / det (m)) * transpose (m); }

  double norm1 ()
  {
    double max_sum  = 0;
    double curr_sum = 0;
    for (size_t i = 0; i < getRowLen (); i++)
    {
      curr_sum = 0;
      for (size_t j = 0; j < getColumnLen (); j++)
      {
        curr_sum += fabs (_data[i][j]);
      }
      max_sum = std::max (max_sum, curr_sum);
    }

    return max_sum;
  }

  double norm2 ()
  {
    double max_sum  = 0;
    double curr_sum = 0;
    for (size_t j = 0; j < getColumnLen (); j++)
    {
      curr_sum = 0;
      for (size_t i = 0; i < getRowLen (); i++)
      {
        curr_sum += fabs (_data[i][j]);
      }
      max_sum = std::max (max_sum, curr_sum);
    }

    return max_sum;
  }

  double norm3 ()
  {
    std::vector<double> e = eigenvalues (*this);
    return pow (*std::max_element (e.begin (), e.end ()), 1 / 2)
           * det (transpose (*this)) * det (*this);
  }

  // число обусловленностей по конкретной норме
  friend double myu (Matrix m, unsigned int norm)
  {
    switch (norm)
    {
    case 1:
      return m.norm1 () * reverse (m).norm1 ();
    case 2:
      return m.norm2 () * reverse (m).norm2 ();
    case 3:
      return m.norm3 () * reverse (m).norm3 ();
    }

    printf ("Error : bad norm number in myu()\n");
    exit (1);

    return -1;
  };
};
}

using namespace MyMatrix;

// ссылку для аргумента matrix пришлось убрать, чтобы в cout можно было
// подавать выражения из матриц
std::ostream &operator<< (std::ostream &out, Matrix matrix)
{
  int max_len_of_elem  = 0;
  int curr_len_of_elem = 0;
  int diff             = 0;

  for (size_t i = 0; i < matrix.getRowLen (); i++)
  {
    for (size_t j = 0; j < matrix.getColumnLen (); j++)
    {
      curr_len_of_elem = std::to_string (matrix.getElem (i, j)).length ();
      max_len_of_elem  = std::max (curr_len_of_elem, max_len_of_elem);
    }
  }

  for (size_t i = 0; i < matrix.getRowLen (); i++)
  {
    out << "|";
    for (size_t j = 0; j < matrix.getColumnLen (); j++)
    {
      diff
          = max_len_of_elem - std::to_string (matrix.getElem (i, j)).length ();

      for (size_t k = 0; k < diff; k++)
        out << " ";

      out << matrix.getElem (i, j);
      if (j != matrix.getColumnLen () - 1)
        out << " ";
    }
    out << "|" << std::endl;
  }
  out << std::endl;
  return out;
}

Matrix Diag (Matrix m)
{
  if (!(m.isSquare ()))
  {
    std::cout << "Error : Diag() requires square matrix\n";
    exit (1);
  }

  Matrix D = Matrix (m.getRowLen (), m.getColumnLen ());
  for (int i = 0; i < m.getRowLen (); i++)
  {
    D.setElem (i, i, m.getElem (i, i));
  }

  return D;
}

Matrix Lower (Matrix m)
{
  if (!(m.isSquare ()))
  {
    std::cout << "Error : Lower function requires square matrix\n";
    exit (1);
  }

  Matrix L = Matrix (m.getRowLen (), m.getColumnLen ());

  for (int i = 0; i < m.getRowLen (); i++)
  {
    for (int j = 0; j < i; j++)
    {
      L.setElem (i, j, m.getElem (i, j));
    }
  }

  return L;
}

Matrix Upper (Matrix m)
{
  if (!(m.isSquare ()))
  {
    std::cout << "Error : Upper() requires square matrix\n";
    exit (1);
  }

  Matrix U = Matrix (m.getRowLen (), m.getColumnLen ());

  for (int i = 0; i < m.getRowLen (); i++)
  {
    for (int j = 0; j < i; j++)
    {
      U.setElem (j, i, m.getElem (j, i));
    }
  }

  return U;
}

// спектральный радиус (только для матрицы 2x2)
double spectral_radius (Matrix m)
{
  if (!m.isSquare ())
  {
    std::cout << "Error : spectral_radius() requires square matrix\n";
    exit (1);
  }

  if (m.getRowLen () != 2)
  {
    std::cout << "Error : spectral_radius() calculates only 2x2 matrixes\n";
    exit (1);
  }

  auto D         = Diag (m);
  auto D_inverse = D;

  D_inverse.setElem (0, 0, 1.0 / D.getElem (0, 0));
  D_inverse.setElem (1, 1, 1.0 / D.getElem (1, 1));

  Matrix Rj = D_inverse * (Lower (m) + Upper (m));

  std::vector<double> ev = eigenvalues (Rj);
  std::vector<double> abs_ev;

  for (double x : ev)
    abs_ev.push_back (std::fabs (x));

  if (abs_ev.size () == 0)
  {
    std::cout << "0 eigenvalues";
    exit (1);
  }
  if (abs_ev.size () == 1)
    return abs_ev[0];
  return *std::max_element (abs_ev.begin (), abs_ev.end ());
}

// оптимальный параметр релаксации
double opt_relax_param (Matrix m)
{
  return 2.0 / (1 + std::sqrt (1 - pow (spectral_radius (m), 2)));
}

// true если |v1[i] - v2[i]| < EPSILON для любого i, иначе false
bool compare_vectors (std::vector<double> &v1, std::vector<double> &v2)
{
  if (v1.size () != v2.size ())
  {
    printf ("Error : compare_vectors() requires equal sizes\n");
    exit (1);
  }

  double EPSILON = 0.001;
  for (int i = 0; i < v1.size (); i++)
    if (fabs (v1[i] - v2[i]) > EPSILON)
      return false;

  return true;
}

// Красивый вывод СЛУ
void print_SLE (Matrix matrix, std::vector<double> f)
{
  int max_len_of_elem  = 0;
  int curr_len_of_elem = 0;
  int diff             = 0;

  for (size_t i = 0; i < matrix.getRowLen (); i++)
  {
    for (size_t j = 0; j < matrix.getColumnLen (); j++)
    {
      curr_len_of_elem = std::to_string (matrix.getElem (i, j)).length ();
      max_len_of_elem  = std::max (curr_len_of_elem, max_len_of_elem);
    }
  }
  int x_index = 0;

  for (size_t i = 0; i < matrix.getRowLen (); i++)
  {
    std::cout << "|";
    for (size_t j = 0; j < matrix.getColumnLen (); j++)
    {
      diff
          = max_len_of_elem - std::to_string (matrix.getElem (i, j)).length ();

      for (size_t k = 0; k < diff; k++)
        std::cout << " ";

      std::cout << matrix.getElem (i, j);
      if (j != matrix.getColumnLen () - 1)
        std::cout << " ";
    }
    std::cout << "|";

    if (i >= (matrix.getRowLen () - matrix.getColumnLen ()) / 2)
      x_index++;

    if (i == matrix.getRowLen () / 2)
      std::cout << " * ";
    else
      std::cout << "   ";

    if ((x_index > 0) and (x_index <= matrix.getColumnLen ()))
    {
      std::cout << "|" << "x" << x_index << "|";
    }
    else
    {
      for (int k = 0; k < 3 + std::to_string (x_index).size (); k++)
        std::cout << " ";
    }
    if (i == matrix.getRowLen () / 2)
      std::cout << " = ";
    else
      std::cout << "   ";

    std::cout << "|" << f[i] << "|" << std::endl;
  }
}

// Можно проверить матрицу на диагональное преобладание, прежде чем сувать ее в
// метод Якоби
bool diag_dominance (Matrix m)
{
  if (!m.isSquare ())
  {
    printf ("Error: diag_dominance requires square matrix\n");
    exit (1);
  }

  double curr_sum = 0;
  for (int i = 0; i < m.getRowLen (); i++)
  {
    curr_sum = 0;
    for (int j = 0; j < m.getColumnLen (); j++)
    {
      if (i != j)
      {
        curr_sum += fabs (m.getElem (i, j));
      }
    }
    if (fabs (m.getElem (i, i) <= curr_sum))
      return false;
  }

  return true;
}

// Решение СЛУ nxn методом Якоби
std::vector<double> solve_SLE_Jacobi (Matrix m, std::vector<double> f)
{
  if (!m.isSquare ())
  {
    printf ("Error : solve_SLE_Jacobi() requires square matrix\n");
    exit (1);
  }
  int n = m.getRowLen ();

  std::vector<double> prev_res = {};
  std::vector<double> res      = {};

  for (int i = 0; i < n; i++)
  {
    prev_res.push_back (0);
    res.push_back (1);
    // res.push_back (f[i] / m.getElem (i, i));
  }
  double curr_sum = 0;

  // счетчик итераций
  int iter_num = 0;
  while (!compare_vectors (res, prev_res))
  {
    for (int i = 0; i < n; i++)
    {
      prev_res = res;
      curr_sum = 0;
      for (int j = 0; j < n; j++)
      {
        if (j != i)
        {
          curr_sum += m.getElem (i, j) * prev_res[j];
        }
      }

      res[i] = (f[i] - curr_sum) / m.getElem (i, i);
    }
    iter_num++;
    if (iter_num == 100)
    {
      printf ("Error : too many iterations in Jacobi method\n");
      exit (1);
    }
  }

  return res;
}

// Красивый вывод метода Якоби,печатает все итерации
void print_SLE_Jacobi (Matrix m, std::vector<double> f)
{
  if (!m.isSquare ())
  {
    printf ("Error : solve_SLE_Jacobi() requires square matrix\n");
    exit (1);
  }
  int n = m.getRowLen ();

  std::vector<double> prev_res = {};
  std::vector<double> res      = {};

  for (int i = 0; i < n; i++)
  {
    prev_res.push_back (0);
    res.push_back (1);
    // res.push_back (f[i] / m.getElem (i, i));
  }
  double curr_sum = 0;
  int    iter_num = 0;

  auto r0 = m * res;

  for (int j = 0; j < f.size (); j++)
  {
    r0[j] -= f[j];
  }
  std::cout << "Начальная невзяка : " << r0 << std::endl;
  std::cout << "---Решаем методом Якоби систему :\n";
  print_SLE (m, f);
  while (!compare_vectors (res, prev_res))
  {
    for (int i = 0; i < n; i++)
    {
      prev_res = res;
      curr_sum = 0;
      for (int j = 0; j < n; j++)
      {
        if (j != i)
        {
          curr_sum += m.getElem (i, j) * prev_res[j];
        }
      }

      res[i] = (f[i] - curr_sum) / m.getElem (i, i);
    }
    iter_num++;

    if (iter_num == 100)
    {
      printf ("Error : too many iterations in Jacobi method\n");
      exit (1);
    }

    auto r = m * res;

    for (int j = 0; j < f.size (); j++)
    {
      r[j] -= f[j];
    }
    std::cout << iter_num << "-ая итерация ";
    for (int i = 0; i < res.size (); i++)
      std::cout << "x" << i + 1 << "=" << res[i] << " ";
    std::cout << "Невязка :" << r << std::endl;
  }

  std::cout << "Результат : ";

  for (int i = 0; i < res.size (); i++)
    std::cout << "x" << i + 1 << "=" << res[i] << " ";
  std::cout << std::endl;
}

std::vector<double> solve_SLE_Seidel (Matrix m, std::vector<double> f)
{
  if (!m.isSquare ())
  {
    printf ("Error : solve_SLE_Seidel() requires square matrix\n");
    exit (1);
  }

  int n = m.getRowLen ();

  std::vector<double> prev_res = {};
  std::vector<double> res      = {};

  for (int i = 0; i < n; i++)
  {
    prev_res.push_back (0);
    res.push_back (1);
    // res.push_back (f[i] / m.getElem (i, i));
  }
  double curr_sum = 0;
  int    iter_num = 0;

  while (!compare_vectors (res, prev_res))
  {
    for (int i = 0; i < n; i++)
    {
      curr_sum = 0;
      for (int j = 0; j < n; j++)
      {
        if (j != i)
        {
          curr_sum += m.getElem (i, j) * res[j];
        }
      }

      res[i]   = (f[i] - curr_sum) / m.getElem (i, i);
      prev_res = res;
    }

    iter_num++;
    if (iter_num == 100)
    {
      printf ("Error : too many iterations in Seidel method\n");
      exit (1);
    }
  }

  return res;
}

// То же самое, что и функция выше, но еще печатает все итерации
void print_SLE_Seidel (Matrix m, std::vector<double> f)
{
  if (!m.isSquare ())
  {
    printf ("Error : solve_SLE_Seidel() requires square matrix\n");
    exit (1);
  }
  int n = m.getRowLen ();

  std::vector<double> prev_res = {};
  std::vector<double> res      = {};

  for (int i = 0; i < n; i++)
  {
    prev_res.push_back (0);
    res.push_back (1);
    // res.push_back (f[i] / m.getElem (i, i));
  }
  double curr_sum = 0;
  int    iter_num = 0;

  std::cout << "---Решаем методом Зейделя систему :\n";
  print_SLE (m, f);
  while (!compare_vectors (res, prev_res))
  {
    for (int i = 0; i < n; i++)
    {
      prev_res = res;
      curr_sum = 0;
      for (int j = 0; j < n; j++)
      {
        if (j != i)
        {
          curr_sum += m.getElem (i, j) * res[j];
        }
      }

      res[i] = (f[i] - curr_sum) / m.getElem (i, i);
    }

    iter_num++;
    if (iter_num == 100)
    {
      printf ("Error : too many iterations in Seidel method\n");
      exit (1);
    }

    auto r = m * res;

    for (int j = 0; j < f.size (); j++)
    {
      r[j] -= f[j];
    }
    std::cout << iter_num << "-ая итерация ";
    for (int i = 0; i < res.size (); i++)
      std::cout << "x" << i + 1 << "=" << res[i] << " ";
    std::cout << "Невязка " << r << std::endl;
  }
  std::cout << "Результат : ";

  for (int i = 0; i < res.size (); i++)
    std::cout << "x" << i + 1 << "=" << res[i] << " ";
  std::cout << std::endl;
}

double sum_of_vec (std::vector<double> v)
{
  double a = 0;
  for (int i = 0; i < v.size (); i++)
  {
    a += v[i];
  }
  return a;
}

double sum_of_vec_square (std::vector<double> v)
{
  double a = 0;
  for (int i = 0; i < v.size (); i++)
  {
    a += v[i] * v[i];
  }
  return a;
}
double scal_dot (std::vector<double> x, std::vector<double> y)
{
  double a = 0;
  for (int i = 0; i < x.size (); i++)
  {
    a += x[i] * y[i];
  }
  return a;
}

// Метод наименьших квадратов
std::vector<double> LSM (std::vector<double> x, std::vector<double> y)
{
  double k = (x.size () * scal_dot (x, y) - sum_of_vec (x) * sum_of_vec (y))
             / (x.size () * sum_of_vec_square (x)
                - sum_of_vec (x) * sum_of_vec (x));
  double b = sum_of_vec (y) - k * (sum_of_vec (x));
  return { k, b };
}

// Переопределенная система (после приведения к нормальному виду считаю методом
// Якоби)
std::vector<double> solve_overdetermined_SLE (Matrix m, std::vector<double> f)
{
  return solve_SLE_Jacobi (transpose (m) * m, transpose (m) * f);
}

// Просто напечатать нормальный вид системы (не решая)
void print_normalized_SLE (Matrix m, std::vector<double> f)
{
  print_SLE (transpose (m) * m, transpose (m) * f);
}

int main ()
{
  // номер 2
  // 1)
  Matrix              a1 ({
      { 11, -9 },
      { -9, 11 }
  });
  std::vector<double> f1 = { 3, -1 };
  std::cout << myu (a1, 1) << std::endl;
  std::cout << myu (a1, 2) << std::endl;
  // std::cout << myu (a1, 3) << std::endl;
  //   2)
  print_SLE_Jacobi (a1, f1);
  print_SLE_Seidel (a1, f1);
  // здесь начал выскакивать сегфолт
  // double t_opt = opt_relax_param (a1);
  // std::cout << "Оптимальный параметр релаксации " << t_opt << std::endl;

  // номер 3
  // 1)
  Matrix              a2 ({
      { -1, 1 },
      {  4, 3 }
  });
  std::vector<double> f2 = { 2, -1 };
  print_normalized_SLE (a2, f2);

  // auto at = transpose (a2) * a2;
  // std::cout << opt_relax_param (at);

  // Номер 4
  Matrix              a3 ({
      {  2, -1 },
      { -2,  3 },
      { -2,  1 }
  });
  std::vector<double> f3 = { 1, 2, 0 };
  std::vector<double> x1 = { -2, -2 / 3., -2 };
  std::vector<double> y1 = { -1, 2 / 3., 0 };
  print_normalized_SLE (a3, f3);
  std::cout << "x,y: " << solve_overdetermined_SLE (a3, f3) << std::endl;
  print_SLE_Jacobi (transpose (a3) * a3, transpose (a3) * f3);
  // Номер 5
  std::vector<double> x = { 0, 1, 2, 3, 7, 9 };
  std::vector<double> y = { 1, 2, 3, 1, 2, 9 };
  std::cout << "k,b : " << LSM (x, y);
  return 0;
}
