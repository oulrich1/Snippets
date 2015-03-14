#!/usr/bin/env python


"""module docstring"""

import sys
import optparse

# # # DEFAULT MODULE STRUCTURE:
# imports
# constants
# exception classes
# interface functions
# classes
# internal functions & classes


# default values inside
# conditional instead of list comprehension..
def append_greetings(ll):
    new_list=[]
    for item in ll:
        if item == "Hey" or item =="hey":
            new_list.append(item + " There, Buddy!")

    if new_list:
        return new_list
    return ""

my_list = ["Hey", "Hey"]
print [item + " There, Buddy!!" for item in my_list if item == "Hey"]

def even(val):
    return val % 2 == 0

# generators
def my_range_generator(stop):
    value = 0
    while value < stop:
        yield value
        value += 1


for i in my_range_generator(10):
    print i

def main():
    a_list = ["Hey", "Hey"]
    print append_greetings(a_list)
    
    a_list = ["There"]
    print append_greetings(a_list)
    
    a_list = ["Yo"]
    print append_greetings(a_list)

    print [x*x for x in xrange(1,10) if even(x)]

    print sum([4, 16, 36, 64])
    print sum([x*x for x in xrange(1,10) if even(x)])

    print ""

    print sum(x*x for x in xrange(1,10) if even(x))

    print 


main()



# this is the less elegrant approach to determinging 
# whether a condition in the data/list was met. unim
# -pressive, and very common approach
was_ever_x_eq_11 = False;
for x in xrange(1,10):
    if x == 11:
        break;
if not was_ever_x_eq_11:
    print "X is never 11.."
    

# this is significantly more elegant solution to check
# the state of some element in the data.
for x in xrange(1,10):
    if x == 11:
        break;
else:
    print "X is never 11.."
# however it might actually be very helpful to continue 
# iteration if it still needs to continue for the entire 
# list


#try:
#    str();
#except TypeError:
#    
def main():
    return 0

if __name__ == "__main__":
    # executing the main
    print "Main"
    status = main()
    sys.exit(status)
    

