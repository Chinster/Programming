# Exercise 15: Reading Files

# imports argv module a child of sys library
from sys import argv

# assigns argv inputs into variables
script, filename = argv

# opens a file in local directory with the inputted filename
txt = open( filename )
print( "Here's your file %r: " % filename )

# prints out the contents of the file in string form
print( txt.read() )



# Prompts for a new file, reads it again
print( "Type the filename again: ")
file_again = input("> ")

txt_again = open( file_again )

print( txt_again.read() )


# Remember to close files when you are done!
txt.close()
txt_again.close()
