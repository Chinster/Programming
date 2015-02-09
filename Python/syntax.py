# *******************************
# * Collection of Python syntax *
# *******************************
# Comment

# Includes
import os.path
from sys import argv

# Declaration
foo = 100
bar = 6;

# automatic conversions to double, string concat
print ("16.6666...: ", foo / bar, " should be the same.")

# True/False
print (True)
print (3 + 2 < 5 - 7)

# String formatters
foo = '\tyup:%d' % 22
bar = "%r %r" # Undefined raw formatter
print ("%s" % foo)
print ("%s %d %s" % (foo, 6, "merp" + "herp"))
print (foo % (3, "yup"))

# Multi-line string
"""
\tYup
\t\tNope
"""

# Read input
foo = input("How you doin'?")

# Input paramaters, import sys.argv
script, arg1 = argv

# Functions, white space is your block
def print_stuff(arg1, arg2):
    print ("%r, %r" % (arg1, arg2))

def print_stuff_two(*args):
    arg1, arg2 = args
    if not 3 == 4:
        print ("%r, %r" % (arg1, arg2))
        return 2
    elif not (3 == 4 and 3 == 4 or 6 < 5):
        print ("Nope")
        return 0
    else:
        print ("Nope")
        return 0

# File IO
def open_file(name):
    bar = open(name)
    print (bar.read())
    bar.seek(0)
    bar.close()

# For loop
foo = [0, 1, 2, 3, 4, 5]
for number in foo:
    print ("%d" % number)
for i in range(6, 10):
    foo.append(i)
    print ("All the single digits!")

# While loop
while True:
    break

Class Herp (object):
    def __init__ (self, merp):
        yup = 3
    def la_di_da (self):
        print (yup)
