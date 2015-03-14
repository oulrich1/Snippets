
import sys
import getopt


# f(x) = (-x/0.25 + 1)*(-x/0.5 + 1) + (x/0.25)*(-x/0.25 + 2)*(1.64872) + (x/0.5)*(-x/0.25 - 1)*(2.71828)
# g(x) = (-x/0.25 + 1)*(-x/0.5 + 1) + (x/0.25)*(-x/0.25 + 2)*(1.64872) + (x/0.5)*(-x/0.25 - 1)*(2.71828)

# x_arr = [1.25, 1.6]
# y_arr = [f(x_arr[0]), f(x_arr[1])]

# defines a function f(x):
f(x) = e^(2*x) - x

x_arr = [1, 1.25, 1.6]
y_arr = [f(x_arr[0]), f(x_arr[1]), f(x_arr[2])]

def func_lagrange_test(x):
    return y_arr[x]

# def func(x):
#     return ((1+x)^(1/2))

def lagrange_coefficient(k, n):
    g(x) = 1
    for i in xrange(0, n+1):
        if i != k:
            g(x) = g(x) * ((x - x_arr[i])/(x_arr[k] - x_arr[i]))
    return g(x)


def lagrange_polynomial(n):
    h(x) = 0;
    for k in xrange(0, n+1):
        h(x) = h(x) + (lagrange_coefficient(k,n)*func_lagrange_test(k).n())
    return h
    
# # # # # # # # # # # # # # # # # # # # # # #
#
#        TEST THE LAGRANGE POLYNOMIAL
#
# print(f(0.43))
def test_lagrange():
    lp = lagrange_polynomial(2);
    evaluate1 = 1.4
    print expand(lp)
    print "P(", evaluate1, ") =", lp(evaluate1).n()
    print "f(", evaluate1, ") = ", f(1.4)
    print "Absolute Error: ", abs(f(1.4) - lp(evaluate1).n())
    return 0
# print("|Function(", evaluate1, ") - f(", evaluate1, ")|",\
#        lp(evaluate1).n() - func(evaluate1))
#
# # # # # # # # # # # # # # # # # # # # # # #
