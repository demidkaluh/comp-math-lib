
#Метод простых итераций 
def f(x):
    # Замените эту функцию на ваше нелинейное уравнение
    return x**3 - x - 2

def g(x):
    # Преобразование уравнения f(x) = 0 в x = g(x)
    return (x + 2)**(1/3)  # Пример преобразования

def simple_iteration(g, x0, tol=1e-5, max_iter=100):
    x_prev = x0
    for i in range(max_iter):
        x_next = g(x_prev)
        if abs(x_next - x_prev) < tol:
            print(f"Найденный корень: {x_next:.5f} за {i+1} итераций.")
            return x_next
        x_prev = x_next
    print("Достигнуто максимальное количество итераций.")
    return None

# Начальное приближение
x0 = 1.0
root = simple_iteration(g, x0)




# Метод Ньютонна
def f_prime(x):
    # Производная нелинейного уравнения
    return 3*x**2 - 1

def newton_method(f, f_prime, x0, tol=1e-5, max_iter=100):
    x_prev = x0
    for i in range(max_iter):
        x_next = x_prev - f(x_prev) / f_prime(x_prev)
        if abs(x_next - x_prev) < tol:
            print(f"Найденный корень: {x_next:.5f} за {i+1} итераций.")
            return x_next
        x_prev = x_next
    print("Достигнуто максимальное количество итераций.")
    return None

# Начальное приближение
x0 = 1.0
root = newton_method(f, f_prime, x0)



# Метод Ньютона для системы
import numpy as np

def F(x):
    # Cистемa нелинейных уравнений
    return np.array([
        x[0]**2 + x[1]**2 - 4,  # Уравнение 1
        x[0]**2 - x[1] - 1      # Уравнение 2
    ])

def jacobian(x):
    # Mатрицa Якоби для системы
    return np.array([
        [2*x[0], 2*x[1]],  # Производные первого уравнения
        [2*x[0], -1]       # Производные второго уравнения
    ])

def newton_method_system(F, jacobian, x0, tol=1e-5, max_iter=100):
    x_prev = x0
    for i in range(max_iter):
        J = jacobian(x_prev)
        F_val = F(x_prev)
        delta = np.linalg.solve(J, -F_val)  # Решаем систему J * delta = -F
        x_next = x_prev + delta
        
        if np.linalg.norm(delta) < tol:
            print(f"Найденный корень: {x_next} за {i+1} итераций.")
            return x_next
        x_prev = x_next
        
    print("Достигнуто максимальное количество итераций.")
    return None

# Начальное приближение
x0 = np.array([1.0, 1.0])
root = newton_method_system(F, jacobian, x0)



# Обратная итерация 
def g(x):
    # Определите вашу итерационную функцию g(x)
    return np.sqrt(4 - x**2)  # Пример: x = g(x) преобразует уравнение x^2 + y^2 = 4

def fixed_point_iteration(g, x0, tol=1e-5, max_iter=100):
    x_prev = x0
    for i in range(max_iter):
        x_next = g(x_prev)
        
        if abs(x_next - x_prev) < tol:
            print(f"Найденный корень: {x_next:.5f} за {i+1} итераций.")
            return x_next
        
        x_prev = x_next
        
    print("Достигнуто максимальное количество итераций.")
    return None

# Начальное приближение
x0 = 1.0
root = fixed_point_iteration(g, x0)



# Интерполяция полиномом в форме Ньютона 
def divided_differences(x, y):
    n = len(y)
    # таблицa разделенных разностей
    coef = np.zeros((n, n))
    coef[:, 0] = y  # Первый столбец - это значения функции в узлах

    for j in range(1, n):
        for i in range(n - j):
            coef[i][j] = (coef[i + 1][j - 1] - coef[i][j - 1]) / (x[i + j] - x[i])
    
    return coef[0]  # Возвращаем коэффициенты полинома

def newton_interpolation(x, y, X):
    n = len(x)
    coef = divided_differences(x, y)
    result = coef[0]

    for i in range(1, n):
        term = coef[i]
        for j in range(i):
            term *= (X - x[j])
        result += term
    
    return result

# Пример использования
x = np.array([0, 1, 2, 3])  # Узлы интерполяции
y = np.array([1, 2, 0, 5])  # Значения функции в узлах

X = 1.5  # Точка, в которой хотим оценить значение полинома
interpolated_value = newton_interpolation(x, y, X)

print(f"Интерполированное значение в точке {X}: {interpolated_value}")



# форма Лагранжа
def lagrange_interpolation(x, y, X):
    n = len(x)
    result = 0.0
    
    for i in range(n):
        # Вычисляем лагранжев базисный полином L_i(X)
        term = y[i]
        for j in range(n):
            if j != i:
                term *= (X - x[j]) / (x[i] - x[j])
        result += term
    
    return result

# Пример использования
x = np.array([0, 1, 2, 3])  # Узлы интерполяции
y = np.array([1, 2, 0, 5])  # Значения функции в узлах

X = 1.5  # Точка, в которой хотим оценить значение полинома
interpolated_value = lagrange_interpolation(x, y, X)

print(f"Интерполированное значение в точке {X}: {interpolated_value}")



# ИНТЕГРАЛЬЧИКИ

def rectangle_method(f, a, b, n):
    """Метод прямоугольников"""
    h = (b - a) / n
    integral = 0.0
    for i in range(n):
        integral += f(a + i * h) * h
    return integral

def trapezoidal_method(f, a, b, n):
    """Метод трапеций"""
    h = (b - a) / n
    integral = 0.5 * (f(a) + f(b))
    for i in range(1, n):
        integral += f(a + i * h)
    integral *= h
    return integral

def simpson_method(f, a, b, n):
    """Метод Симпсона"""
    if n % 2 == 1:  # n должно быть четным
        n += 1
    h = (b - a) / n
    integral = f(a) + f(b)
    for i in range(1, n, 2):
        integral += 4 * f(a + i * h)
    for i in range(2, n-1, 2):
        integral += 2 * f(a + i * h)
    integral *= h / 3
    return integral

def simpson_38_method(f, a, b, n):
    """Формула Симпсона 3/8"""
    if n % 3 != 0:  # n должно быть кратно 3
        n += (3 - n % 3)
    h = (b - a) / n
    integral = f(a) + f(b)
    
    for i in range(1, n):
        if i % 3 == 0:
            integral += 2 * f(a + i * h)
        else:
            integral += 3 * f(a + i * h)
    
    integral *= 3 * h / 8
    return integral

# Пример использования
def f(x):
    return x ** 2  # Пример функции

a = 0  # Нижний предел интегрирования
b = 1  # Верхний предел интегрирования
n = 10  # Количество подынтервалов

rectangle_result = rectangle_method(f, a, b, n)
trapezoidal_result = trapezoidal_method(f, a, b, n)
simpson_result = simpson_method(f, a, b, n)
simpson_38_result = simpson_38_method(f, a, b, n)

print(f"Метод прямоугольников: {rectangle_result}")
print(f"Метод трапеций: {trapezoidal_result}")
print(f"Метод Симпсона: {simpson_result}")
print(f"Формула Симпсона 3/8: {simpson_38_result}")
