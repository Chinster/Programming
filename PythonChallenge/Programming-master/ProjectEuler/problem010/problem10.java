/**
 * Project Euler - Problem 10 Solution
 * problem10.java.
 *
 * @author Christopher Chin
 *
 */
public class problem10
{

    /**
     * Find the sum of the primes below two million.
     *
     * Could be more efficient. I do not know how to optimize.
     */
    public problem10()
    {
        long primeSums = 2L; //sum includes initial two.
        for( long i = 3; i < 2000000; i+=2 ) //for: odds below two million
        {
            if( isPrime(i) )
            {
                primeSums += i;
            }
        }

        System.out.println( primeSums );
    }

    //from problem 7
    /**
     * Checks if number is prime.
     *
     * @param testNum int
     */
    public static boolean isPrime( long testNum )
    {
        //if( testNum == 1 ) return false; //not in testPrimes
        //if( testNum == 2 ) return true; // not in testPrimes
        for( int i = 3; i <= testNum / i; i += 2 )
            if( testNum % i == 0 )
                return false;
        return true;
    }

    /**
     * MAIN.
     * 
     * @param args String[]
     */
    public static void main( String[] args )
    {
        new problem10();
    }
}
