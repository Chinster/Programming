# Exercise 22: What Do You Know So Far?

# prints strings to stdout
print( 10 )

# % within a string may denote a formatter which is defined by %
print( '%d + %r = %s' % (10, 15, 25) )

# %r is for debugging raw input
print( '%r' % ('\n') )

# %s is for strings
print( '%s' % ('\n') )

# takes input
input()

# Takes input after prompt
input( "> " )

# sys library folds options for argument intake
from sys import argv

# Assigns all values taken as argument to python command to variables
# Assigns string values. Makes it so script call requires x other variables
# first_arg is the file name
filename, second_arg = argv

# opens a file by name. Default mode is 'r', read
reading = open( second_arg )

# returns contents of entire file
reading.read()

# moves where you are looking on file by 
reading.seek( 4 )

# returns a line delimiter=\n
reading.readline()

# Always close your streams!
reading.close()

# opens in write mode. Automatically truncates file.
writing = open( 'ex22.txt', 'w' )

# deletes file contents. Maybe used when in 'a' appending mode?
writing.truncate()

# writes strings to file
writing.write( "Accepts escape characters\nSee?" )

# always close your streams!
writing.close()

# def defines a new function
# return returns any value (type not defined)
# Don't forget the colon and white space!
def new_function():
    return 0 # Such success. Much accomplish. Wow.

# Takes 2 arguments. similar to argv
# Don't forget the colen and white space!
def new_function( *arg ):
    arg1, arg2 = arg
