import java.util.ArrayList;
/**
 * Project Euler - Problem 3 Solution.
 * problem3.java.
 *
 * @author Christopher Chin
 *
 */
public class problem3
{
   private static final double THE_HOLY_NUMBER = 600851475143.0;
    /**
     * Determines the largest prime factor of the holy number.
     * 
     */
    public problem3()
    {
        ArrayList<Integer> factors;
        factors = getPrimeFactors( THE_HOLY_NUMBER );
        int largestPrime = 0;
        for( Integer i: factors ){
           if( i.intValue() > largestPrime )
               largestPrime = i.intValue();
        }
        System.out.println( factors );
        System.out.println( "Largest prime: " + largestPrime );

    }
    /**
     * Returns the prime factors of input int.
     * 
     * @param num int input number
     */
    public static ArrayList<Integer> getPrimeFactors( double num )
    {
        ArrayList<Integer> returnArray = new ArrayList<Integer>();
        double otherFactor = num;
        for( int i = 2; i <= otherFactor/i; i++ )
        {
            if( otherFactor%i == 0 )
            {
                otherFactor = otherFactor/i;
                returnArray.add( new Integer( i ) );
                i = 2;
            }
        }
        returnArray.add( new Integer( (int)otherFactor ) );
        return returnArray;
    }
    /**
     * MAIN.
     * 
     * @param args String[]
     */
    public static void main( String[] args )
    {
        new problem3();
    }
}
