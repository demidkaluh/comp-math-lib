#include <cstdlib>
#include <iostream>
#include <vector>

template <class T> class MyVector
{
public:
  enum class Type
  {
    h,
    v
  };

private:
  std::vector<T> _data = {};
  Type _type; // Горизонтальный или вертикальный вектор?

public:
  MyVector<T> (unsigned int n)
  {
    _type = Type::v;
    for (size_t i = 0; i < n; i++)
      _data.push_back (1);
  }

  MyVector<T> (std::vector<T> data)
  {
    _type = Type::v;
    _data = data;
  }

  MyVector<T> (std::vector<T> data, Type t)
  {
    _type = t;
    _data = data;
  }

  int getSize () const { return _data.size (); }

  T operator[] (int i) const { return _data[i]; }

  MyVector &operator+= (MyVector v)
  {
    if (!checkSizes (*this, v))
    {
      std::cout << "Inequal vector sizes\n";
      exit (1);
    }
  }

  MyVector<T> transpose () const
  {
    MyVector<T> res = *this;

    if (res._type == Type::v)
      res._type = Type::h;
    else
      res._type = Type::v;

    return res;
  }
};

template <class T, class U> bool checkSizes (MyVector<T> &v1, MyVector<U> &v2)
{
  return (v1.getSize () == v2.getSize ());
}

template <class T, class U> auto dotProduct (MyVector<T> v1, MyVector<U> v2)
{
  if (!checkSizes (v1, v2))
  {
    std::cout << "Inequal vector sizes\n";
    exit (1);
  }
  auto res = 0;
  for (size_t i = 0; i < v1.getSize (); i++)
    res += v1[i] * v2[i];

  return res;
}

template <class T, class Y, class P>
MyVector<P> vectorProduct (MyVector<T> &v1, MyVector<Y> &v2)
{
  if ((v1.getSize () != 3) or (v2.getSize () != 3))
  {
    printf ("Error : vector product defined only for 3D vectors\n");
    exit (1);
  }

  return v1;
}

template <typename T>
std::ostream &operator<< (std::ostream &out, MyVector<T> vec)
{
  if (vec.getType () == Type::v)
  {
  }
  else
  {
  }

  return out;
}

int main ()
{
  MyVector<double> v1 ({ 1.1, 2.22, 2.5 });
  MyVector<double> v2 ({ 2.5, 3.223, 1.711 });

  std::cout << dotProduct (v1, v2);
  return EXIT_SUCCESS;
}
