# Exercise 21: Functions Can Return Something

def add( a, b ):
    print( "ADDING %d + %d." % (a,b) )
    return a + b

def subtract( a, b ):
    print( "SUBTRACTING %d - %d." % (a,b) )
    return a - b

def multiply( a, b ):
    print( "MULTIPLYING %d * %d." % (a,b) )
    return a * b

def divide( a, b ):
    print( "DIVIDING %d / %d." % (a,b) )
    return a / b

print( "Let's do some math with just functions!" )

age = add( 13, 6 )
height = subtract( 78, 12 )
weight = multiply( 26, 5 )
iq = divide( 100, 2 )

print( "Age: %d, Height: %d, Weight %d, IQ: %d" % (age, height, weight, iq ) )

what = add( age, subtract( height, multiply( weight, divide( iq, 2 ) ) ) )

print( "That becomes: ", what );
