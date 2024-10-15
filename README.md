## comp-math-lib 
Здесь реализован класс матриц и разные вещи для вычматов, а именно: 

## Собственные значения, спектральный радиус, оптимпльный параметр релаксации (для матриц 2х2) 
std::vector<double> eigenvalues (Matrix m) 
double spectral_radius (Matrix m) 
double opt_relax_param (Matrix &m) 

## Методы Якоби|Зейделя|Верхней релаксации

Для начала можно проверить матрицу на диагональное преобладание: 
bool diag_dominance (Matrix m) 

# Решение СЛУ nxn методом Якоби 
std::vector<double> solve_SLE_Jacobi (Matrix &m, std::vector<double> f) 

# Красивый вывод метода Якоби,печатает все итерации 
void print_SLE_Jacobi (Matrix &m, std::vector<double> f) 

# Аналогично для Зейделя:
std::vector<double> solve_SLE_Seidel (Matrix &m, std::vector<double> f) 
void print_SLE_Seidel (Matrix &m, std::vector<double> f) 

## Переопределенная система 
# Решить : 
std::vector<bool> solve_overdetermined_SLE (Matrix m, std::vector<double> f) 

# Просто напечатать нормальный вид переопределенной системы (не решая) 
void print_overdetermined_SLE (Matrix m, std::vector<double> f) 
