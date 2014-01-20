#Summates the even value terms of the Fibonnaci sequence.
def problem2( lim ):
	prev = 1
	current = 1
	sum = 0
	while( current < lim ):
		if( current % 2 == 0 ):
			sum += current
		holder = current
		current += prev
		prev = holder
	out = "Summation of even values in Fibonnaci sequence up until " +  str(lim) + ": " + str(sum)
	print out
problem2( 4000000 )
