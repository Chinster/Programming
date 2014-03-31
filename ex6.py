# Exercise 6: Strings and Text


# variable declaration with a formatter
x = "There are %d types of people." % 10

binary = "binary"
do_not = "don't"

# variable declaration with multiple formatters
y = "Those who know %s and those who %s" % (binary, do_not)

print( x )
print( y )

# formatter for raw versions of variables, used for debugging
print( "I said: %r." %x)

# formatter for string
print( "I also said: '%s'." % y )

hilarious = False
# variable with undefined formatter
joke_evaluation = "Isn't that joke no funny!? %r"

# formatter into variable with undefined formatter
print( joke_evaluation % hilarious )
# formatter does not alter original variable?
print( joke_evaluation % True )


w = "This is the left side of..."
e = "a string with a right side."
print( w + e )
