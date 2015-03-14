
import sys
import getopt

import timeit
import time

from sage.symbolic.integration.integral import indefinite_integral


ACCEPTABLE_ERROR_CONST = 1e-20

# # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#     ITERATIVE METHODS FOR ROOT-FINDING
#
#   bisection_method
#   newtons_method
#   alternative_newtons_method
#
#   By:     Oriah Ulrich
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # #


# # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#
#   Bisection method essentially cuts the interval in
#   half and runs on the new interval where it is ob-
#   vious there is a root because of change in sign of
#  'f'. The method halts when f is close enough to 0.. 
#   or when p isnt changing hardly at all
#
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # #

def bisection_method(func, a0, b0, accepted_error=None):
    if accepted_error == None:
        accepted_error = ACCEPTABLE_ERROR_CONST # 1E-14
    a = a0
    b = b0
    p = (a0+b0)/2
    f_p = func(p).n()

    i = 0
    #while abs(f_p) > accepted_error:
    start = time.time()
    while abs(f_p) > accepted_error:
        if f_p == 0: # or abs(f_p) <= accepted_error:
            break
        comparison = func(a).n()*f_p
        if comparison < 0:
            a = a
            b = p
        else:
            a = p
            b = b
        p = (a + b) / 2
        f_p = func(p).n()
        i += 1
        print "Iteration: ", i, " p = ", p.n(), " f(p) = ", f_p
    end = time.time()

    print "Total Iterations: ", i, ". Final p = ", p.n()
    print "Time: ", end - start, "[s]"
    print
    return p


# # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#
#   Newtons method is a simliar idea to Bisection Method, 
#   and uses similar halting methods. However, newtons
#   method examines the rate of change of the function,
#   which requires the derivative is known of some function
#   
#   If the function is unknown, then the data points could
#   be approximated by a curve fit or a best fit polynomial..
#   which could then have it's derivative taken...
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # #

def newtons_method(func, a, b, accepted_error=None):
    if accepted_error == None:
        accepted_error = ACCEPTABLE_ERROR_CONST # 1E-14

    deriv_func = derivative(func, x)
    
    # LIMIT THE NUMBER OF ITERATIONS
    # TO REASONABLE NUMBER
    MAX_ITERATIONS = 100

    # select arbitary starting point
    cur_p   = (a+b)/2
    cur_f_p = func(cur_p).n()

    i = 0 # comparing the domain to check for stopping point
    start = time.time()
    while abs(cur_f_p) > accepted_error:
        if i > MAX_ITERATIONS or cur_f_p == 0:
            break

        # try to detect the derivative..
        try:
            deriv_func_at_cur_p = deriv_func(cur_p).n()
        except Exception, e:
            print "Divide by zero probably occured.. breaking"
            raise
        else:
            pass

        if abs(deriv_func_at_cur_p) == 0 :
            print "Derivative will approach 0 soon, (preventing divide by 0, exiting...)"
            break
        else:  
            cur_p = cur_p - cur_f_p/deriv_func_at_cur_p
        cur_f_p = func(cur_p).n()
        i += 1
        print "Iteration: ", i, " p = ", cur_p.n(), " f(p) = ", cur_f_p
    end = time.time()

    print "Total Iterations: ", i, ". final p = ", cur_p.n()
    print "Time: ", end - start, "[s]"
    print
    return cur_p


# # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#
#   Alternative Newtons Method: tries to avoid divide by
#   zero issues, when we take the derivative of f(x) but 
#   at p the f`(x) approaches 0.. quicker than f(x)..
#   computers cannot divide like that.. so we let the ratio
#   be of f(x)/f`(x) and (f(x)/f`(x))`
#
#   (m/m`) = (f(x)/f`(x) / (f(x)/f`(x))`)
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # #

def alternative_newtons_method(func, a, b, accepted_error=None):
    if accepted_error == None:
        accepted_error = ACCEPTABLE_ERROR_CONST # 1E-100

    deriv_func  = derivative(func, x)    # important for 0 testing
    m(x)        = func(x)/deriv_func     # meu of x
    m_prime(x)  = derivative(m, x)       # meu prime of x

    # LIMIT THE NUMBER OF ITERATIONS
    # TO REASONABLE NUMBER
    MAX_ITERATIONS = 10

    # select arbitary starting point
    p   = (a+b)/2
    f_p = func(p).n()   # check for f_p to be 0.. or
                        # close to zero by R(x) (error bound)

    m_p       = m(p).n()    # alternate newtons method..
    m_prime_p = m_prime(p).n()
    
    i = 0 
    start = time.time()
    while abs(f_p) > accepted_error:    # f_p close to 0
        if i > MAX_ITERATIONS or f_p == 0:
            break

        # try to detect the derivative.. to prevent divide by 0
        try:
            m_prime_p = m_prime(p).n()
        except Exception, e:
            print "Divide by zero probably occured.. breaking"
            raise
        else:
            pass

        if abs(m_prime_p) == 0 :
            print "Derivative will approach 0 soon,\
                  (preventing divide by 0, exiting...)"
            break
        p = p - m_p/m_prime_p
        m_p = m(p).n()
        m_prime_p = m_prime(p).n()
        f_p = func(p).n()
        i += 1
        print "Iteration: ", i, " p = ", p.n(), " f(p) = ", f_p
    end = time.time()   

    print "Total Iterations: ", i, ". final p = ", p.n()
    print "Time: ", end - start, "[s]"
    print
    return p



# ENTRY POINT:

def main():
    print "Main:::\n"

    # g(x) = cos(x/3) - 2*cos(x/5) + 5*sin(x/4) + 8 
    # p = plot(indefinite_integral(g(x),x), 100, 600)
    # p.show()

    f(x) = x^3 - 3*x^2*(2^-x) + 3*x*(4^-x) - 8^-x  
    p = plot(f(x),x, 0.6, 0.7)
    p.show()

    v = [-10,200]
    v = [-100,100]
    print "FUNCTION: f =", f, "\n"
    print "ACCEPTABLE_ERROR_CONST: ", ACCEPTABLE_ERROR_CONST, "\n"
    print "INTERVAL: v =", v, "\n"
    #0.6411895751953125

    interval_left  = v[0]
    interval_right = v[1]

    print "BISECTION METHOD:"
    retval = bisection_method(f, interval_left, interval_right)
    # print retval.n()

    print "NEWTONS METHOD:"
    retval = newtons_method(f, interval_left, interval_right)
    # print retval.n()

    print "ALTERNATIVE NEWTONS METHOD:"
    retval = alternative_newtons_method(f, interval_left, interval_right)
    # print retval.n()

    return 0

# set if run as script
# or if run as module but file is main.py
if __name__ == "__main__":
    # executing the main
    status = main()