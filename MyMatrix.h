#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

/*
 Здесь реализован шаблонный класс матриц Matrix.
 Пока матрицы умеют складываться (+,+=), умножаться (*, *=), транспонироваться
 и даже(!) возводиться в степень.
 Есть 3 конструктора : Matrix() - матрица
 ранга 0. Matrix(int n) - единичная матрица ранга n.
 Matrix(vector<vector<T>> data) - делает из поданного вектора векторов
 хорошую матрицу.
 Можно вывести через cout. В целом всё.
*/

std::ostream &operator<< (std::ostream &out, MyMatrix::Matrix matrix);
Matrix        Diag (Matrix m);
Matrix        Lower (Matrix m);
Matrix        Upper (Matrix m);
double        spectral_radius (Matrix m);
double        opt_relax_param (Matrix m);
bool compare_vectors (std::vector<double> &v1, std::vector<double> &v2);
void print_SLE (Matrix matrix, std::vector<double> f);
bool diag_dominance (Matrix m);
std::vector<double> solve_SLE_Jacobi (Matrix m, std::vector<double> f);
void                print_SLE_Jacobi (Matrix m, std::vector<double> f);
std::vector<double> solve_SLE_Seidel (Matrix m, std::vector<double> f);
void                print_SLE_Seidel (Matrix m, std::vector<double> f);
double              sum_of_vec (std::vector<double> v);
double              sum_of_vec_square (std::vector<double> v);
double              scal_dot (std::vector<double> x, std::vector<double> y);
std::vector<double> LSM (std::vector<double> x, std::vector<double> y);
std::vector<double> solve_overdetermined_SLE (Matrix m, std::vector<double> f);
void                print_normalized_SLE (Matrix m, std::vector<double> f);
