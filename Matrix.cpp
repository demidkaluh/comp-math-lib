#include <iostream>
#include <vector>

class Matrix
{
private:
  std::vector<std::vector<double> > _data;

  int _row;
  int _column;

public:
  // Единичная матрица NxM
  // Matrix (int n, int m) {}

  // Единичная матрица NxN
  Matrix (int n)
  {
    _row    = n;
    _column = n;
  }

  Matrix (std::vector<std::vector<double> > &data) { _data = data; }

  int getRowLen () const { return _row; }
  int getColumnLen () const { return _column; }

  bool checkRows (Matrix &m) const { return (_row == m.getRowLen ()); }

  bool checkColumns (Matrix &m) const
  {
    return (_column == m.getColumnLen ());
  }

  bool checkSizes (Matrix &m) const
  {
    return (checkRows (m) and checkColumns (m));
  }

  Matrix operator+= (const Matrix &m) {}

  Matrix operator+ (const Matrix &m) const
  {
    if (!checkSizes (m))
    {
      throw "Error : Inequal dimensions\n";
    }

    *this += m;
    return *this;
  }
};

std::ostream &operator<< (std::ostream &out, Matrix &matrix)
{
  for (std::vector<double> row : matrix)
  {
    for (double elem : matrix)
    {
      out << elem << " ";
    }
    out << std::endl;
  }

  return out;
}

int main () { return 0; }
