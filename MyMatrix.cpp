#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

/*
 Здесь реализован шаблонный класс матриц MyMatrix.
 Пока матрицы умеют складываться (+,+=), умножаться (*, *=) и
 транспонироваться.
 Есть 3 конструктора :
 MyMatrix() - матрица ранга 0.
 MyMatrix(int n) - единичная матрица ранга n.
 MyMatrix(vector<vector<T>> data) - делает из поданного вектора векторов
 хорошую матрицу.
 Можно вывести через cout. В целом всё.
*/

template <class T> class MyMatrix
{
private:
  std::vector<std::vector<T> > _data = {};

public:
  // Просто какая-то пустая матрица нулевой размерности
  MyMatrix () {}

  // Единичная матрица NxN
  MyMatrix<T> (int n)
  {
    std::vector<T> curr_row = {};
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

  MyMatrix (std::vector<std::vector<T> > data)
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

  bool checkRows (MyMatrix &m) const
  {
    return (getRowLen () == m.getRowLen ());
  }

  bool checkColumns (MyMatrix &m) const
  {
    return (getColumnLen () == m.getColumnLen ());
  }

  void checkSizes (MyMatrix &m) const
  {
    if (!(checkRows (m) and checkColumns (m)))
    {
      std::cout << "Error : Inequal dimensions\n";
      exit (1);
    }
  }

  T getElem (unsigned int r, unsigned int c) const
  {
    if ((r >= getRowLen ()) or (c >= getColumnLen ()))
    {
      std::cout << "Error : incorrect reference to the element of matrix\n";
      exit (1);
    }
    return _data[r][c];
  };

  void setElem (unsigned int r, unsigned int c, T val) { _data[r][c] = val; }
  void addRow (std::vector<T> row) { _data.push_back (row); }

  MyMatrix transpose () const
  {
    MyMatrix<T> m_copy;

    std::vector<T> curr_row = {};

    for (size_t j = 0; j < getColumnLen (); j++)
    {
      for (size_t i = 0; i < getRowLen (); i++)
        curr_row.push_back (0);

      m_copy._data.push_back (curr_row);
      curr_row = {};
    }

    for (size_t i = 0; i < getRowLen (); i++)
    {
      for (size_t j = 0; j < getColumnLen (); j++)
        m_copy.setElem (j, i, getElem (i, j));
    }

    return m_copy;
  }

  MyMatrix &operator+= (MyMatrix m)
  {
    checkSizes (m);

    for (size_t i = 0; i < getRowLen (); i++)
      for (size_t j = 0; j < getColumnLen (); j++)
        this->_data[i][j] += m.getElem (i, j);

    return *this;
  }

  friend MyMatrix operator+ (MyMatrix m1, MyMatrix m2)
  {
    m1.checkSizes (m2);
    MyMatrix tmp_m = m1;
    tmp_m += m2;

    return tmp_m;
  }

  MyMatrix &operator*= (MyMatrix m)
  {
    if (this->getColumnLen () != m.getRowLen ())
    {
      std::cout << "Error : inequal dimensions for multiplication\n";
      exit (1);
    }

    MyMatrix m_copy = *this;
    _data           = {};

    std::vector<T> curr_row = {};
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

  friend MyMatrix operator* (MyMatrix m1, MyMatrix m2)
  {
    if (m1.getColumnLen () != m2.getRowLen ())
    {
      std::cout << "Error : inequal dimensions for multiplication\n";
      exit (1);
    }
    MyMatrix tmp_m = m1;
    tmp_m *= m2;

    return tmp_m;
  }
};

// ссылку для аргумента matrix пришлось убрать, чтобы в cout можно было
// подавать выражения из матриц
template <class T>
std::ostream &operator<< (std::ostream &out, MyMatrix<T> matrix)
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

int main ()
{
  MyMatrix<int> m1;
  MyMatrix<int> m2 = MyMatrix<int> ({
      { 1, 2, 5 },
      { 3, 4, 7 },
      { 1, 5, 4 }
  });
  MyMatrix<int> m3 = MyMatrix<int> ({
      {   3, 17,  6 },
      {   4,  0, 12 },
      { 192,  2,  9 }
  });

  MyMatrix<int> m4 = MyMatrix<int> ({
      { 1, 2, 3 },
      { 4, 5, 6 }
  });

  MyMatrix<int> m5 = MyMatrix<int> ({
      { 1, 2 },
      { 3, 4 },
      { 5, 6 }
  });

  std::cout << m2 + m3;
  std::cout << m4 << m4.transpose ();
  MyMatrix<int> E (2);
  std::cout << m3 * m2;
  auto m = (m4 * m5) + E;
  std::cout << m;

  return 0;
}
