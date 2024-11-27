from math import *
import numpy as np
pi = np.pi

#Метод простых итераций  (Задачка 1)
def g(x):
    return -1/8 * (np.exp(0.5 * x + 3) + 4)

def simple_iteration(g, x0=-0.5, epsilon=1e-3, max_iter=100):
    x = x0
    for i in range(max_iter):
        x_new = g(x)
        if abs(x_new - x) < epsilon:
            return x_new, i  
        x = x_new

    return None 

# Метод Ньютонa (задачка 2)
def g_prime(x):
    return -1/8 * (1/2*np.exp(0.5*x+3))

def newton_method(f, f_prime, x0 = 1.0, tol=1e-5, max_iter=100):
    x_prev = x0
    for i in range(max_iter):
        x_next = x_prev - f(x_prev) / f_prime(x_prev)
        if abs(x_next - x_prev) < tol:
            return x_next
        x_prev = x_next

    return None

#Система для задачи 3
def F(x):
    return np.array([
        3*cos(2*pi*x[0]+pi*x[1])+2*x[0]**2+x[1]**2+x[0]*x[1]-3*x[0]-2*x[1]-2,
        2*sin(pi*x[0]+2*pi*x[1]+pi/2)+3*x[0]**2+x[1]**2+2*x[0]*x[1]-4*x[0]-3*x[1]-3
        ])

# Ее якобиан
def jacobian(x):
    return np.array([
        [4*x[0]+x[1]-6*pi*sin(2*pi*x[0]+pi*x[1])-3, x[0]+2*x[1]-3*pi*sin(2*pi*x[0]+pi*x[1])],          
        [6*x[0]+2*x[1]-2*pi*sin(pi*x[0]+2*pi*x[1])-4, 2*x[0]+2*x[1]-4*pi*sin(pi*x[0]+2*pi*x[1])-3]       
    ])

def newton_method_system(F, jacobian, x0, tol=1e-5, max_iter=100):
    x_prev = x0
    for i in range(max_iter):
        J = jacobian(x_prev)
        F_val = F(x_prev)
        delta = np.linalg.solve(J, -F_val)  
        x_next = x_prev + delta
        
        if np.linalg.norm(delta) < tol:
            return x_next
        x_prev = x_next
        
    return None


# Интерполяция полиномом в форме Ньютона 
def divided_difference(x, y):
    n = len(y)
    coeffs = np.zeros((n, n))
    coeffs[:, 0] = y  

    for j in range(1, n):
        for i in range(n - j):
            coeffs[i][j] = (coeffs[i + 1][j - 1] - coeffs[i][j - 1]) / (x[i + j] - x[i])
    
    return coeffs[0]   

def newton_interpolation(x, y, y_target):
    n = len(x)
    coeffs = divided_difference(x, y)

    def P(t):
        total = coeffs[0]
        for i in range(1, n):
            term = coeffs[i]
            for j in range(i):
                term *= (t - x[j])
            total += term
        return total

    a, b = min(x), max(x)   
    tol = 1e-6
    max_iter = 100

    for _ in range(max_iter):
        mid = (a + b) / 2
        P_mid = P(mid) - y_target
        
        if abs(P_mid) < tol:
            return mid
        elif P_mid > 0:
            b = mid
        else:
            a = mid
            
    return None


# ИНТЕГРАЛЬЧИКИ

def rectangle_method(f, a, b, n):
    h = (b - a) / n
    integral = 0.0
    for i in range(n):
        integral += f(a + i * h) * h
    return integral

def trapezoidal_method(f, a, b, n):
    h = (b - a) / n
    integral = 0.5 * (f(a) + f(b))
    for i in range(1, n):
        integral += f(a + i * h)
    integral *= h
    return integral

def simpson_method(f, a, b, n):
    if n % 2 == 1:
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

#Формулой прямоугольников, но f задана вектором точек (x,y) (для 6 задачи)
def rectangle_integration(x, f):
    res = 0.0
    
    for i in range(len(x) - 1):
        width = x[i + 1] - x[i]
        height = f[i]
        area = width * height
        res += area
    
    return res

def inverse_interpolation(x, y, y_target):
    for i in range(4):
        if (y[i] <= y_target <= y[i + 1]) or (y[i] >= y_target >= y[i + 1]):
            x_target = x[i] + (y_target - y[i]) * (x[i + 1] - x[i]) / (y[i + 1] - y[i])
            return x_target
    return None

def main():
    #Задачка 1
    res1 = simple_iteration(g)
    print (f"Задачка 1 : {res1}")

    #Задачка 2 
    res2 = newton_method (g, g_prime);
    print (f"Задачка 2 : {res2}")

    #Задачка 3 
    x0 = [1.0, 1.0]
    res3 = newton_method_system(F, jacobian, x0)
    print (f"Задачка 3 : {res3}")

    #Задачка 4 
    x = [-7.3, -5.3, -1.3, 6.7, 22.7]
    f = [4,2,1,-1,-2]
    target = 0
    res4 = inverse_interpolation (x, f, target)
    print (f"Задачка 4 : {res4}")

    #Задачка 5 
    x = [-2, -1, 1, 3, 4]  
    y = [79, 14, -2, -26, -11]  
    X = 2

    res5 = newton_interpolation(x, y, X)
    print (f"Задачка 5 : {res5}")

    #Задачка 6
    x = [1,3,4,6,7,8,9]
    f = [11.6, 24.8, 29, 26.6, 17.6, 1.8, -22]
    res6 = rectangle_integration(x,f)
    print (f"Задачка 6 : {res6}");
    
    return None

main()
