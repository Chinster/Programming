import java.util.ArrayList;
/**
 * Project Euler - Problem 7 Solution.
 * problem7.java.
 *
 * @author Christopher Chin
 *
 */
public class problem7
{
    
    /**
     * Find the 10001st prime.
     *
     */
    public problem7()
    {
        ArrayList<Integer> factors;
        int counter = 1; //already counting 2.
        double testPrime = 3;
        while( counter < 10001 )
        {
            if( isPrime( testPrime ) )
                counter++;
            testPrime += 2;
        }
        System.out.println( "10001st prime: " + (testPrime - 2) );

    }
    /**
     * Checks if number is prime.
     *
     * @param testNum double
     */
    public static boolean isPrime( double testNum )
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
        new problem7();
    }
}
