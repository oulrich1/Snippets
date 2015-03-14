#! /usr/env python
import os
import numpy
from   fractions import Fraction

# From that one time in Parallel/"Numerical" Lab

# a = np.matrix('3 2 8 1 4; 4 1 3 6 3; 5 2 6 1 2; 8 3 3 2 1;')

def subract_vector(v1, v2):
    v3 = []
    # print len(v1)
    for i in xrange(0, len(v1)):
        v3.append(v1[i] - v2[i])
        pass
    return v3


def mult_vector(v1, constant):
    v3 = []
    # print len(v1)
    for i in xrange(0, len(v1)):
        v3.append(v1[i] * constant)
        pass
    return v3


def print_matrix(mat):
    for i in xrange(0, len(mat)):
        # for j in xrange(0, len(mat[i])):
        #     print Fraction("{0:.5f}".format(mat[i][j]))
        # pass
        print mat[i]
    return

# print subract_vector([3,2,8,1], [4,1,3,6])


row1 = [3.0, 2.0, 8.0, 1.0, 4.0]
row2 = [4.0, 1.0, 3.0, 6.0, 3.0]
row3 = [5.0, 2.0, 6.0, 1.0, 2.0]
row4 = [8.0, 3.0, 3.0, 2.0, 1.0]


mat = [  row1,
         row2,
         row3,
         row4  ]


def reduce_triangle(mat):
    matrix = mat
    for row in xrange(0, len(matrix)):
        # print matrix[row]
        for x in xrange(0, row):
            print row, x
            matrix[row] = subract_vector(matrix[row], mult_vector(matrix[x], (matrix[row][x] / matrix[x][x]))) 
            pass
        # print ""
        pass
    return matrix


def back_substitution(mat):
    x_vec = [0] * (len(mat[0])-1)
    b_vec = [0] * len(mat)

    for b in xrange(0, len(mat)):
        b_vec[b] = mat[b][len(mat[0])-1]
        pass

    for j in xrange(len(mat)-1, -1, -1):
        # print "J: ", j
        # print b_vec[j]
        x_vec[j] = b_vec[j] / mat[j][j]
        for i in xrange(j-1, -1, -1):
            # print "    I: ", i
            b_vec[i] = b_vec[i] - mat[i][j]*x_vec[j]
            pass
        pass
    return x_vec


def row_reduce(matrix):
    mat = reduce_triangle(matrix)
    print "Reduced Upper Triangle: "
    print_matrix(mat)

    X = back_substitution(mat)
    print "X Solution: "
    print X

    # fractions
    print ""
    print"Fractions using Fraction(): maybe there is a good way?"
    for x in xrange(0, len(X)):
        print Fraction(X[x])

    return mat

row_reduce(mat)

