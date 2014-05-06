# Exercise 33: While Loops

def zeroTo( upper ):
    i = 0
    numbers = []
    while i < upper:
        print( "At the top i is %d" % i )
        numbers.append( i )

        i = i + 1
        print( "Numbers now: ", numbers )
        print( "At the bottom i is %d" % i )
    print ("The numbers: " )
    for num in numbers:
        print( num )
    return numbers

zeroTo( 6 )
