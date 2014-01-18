#Summates numbers divisible by 3 or 5.
def problem1( lim ):
	sum = 0
	for num in range(0, lim ):
		if( num% 3 == 0 or num % 5 == 0 ):
			sum += num
	print sum
problem1( 1000 )
