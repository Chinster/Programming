import java.util.ArrayList;
/**
 * ProjectEuler - Problem 12 Solution
 * problem12.java.
 *
 * @author Christopher Chin
 *
 */
public class problem12
{
    
    /**
     * First triangle number to have over 500 divisors.
     * Divisor =
     * Triangle number = sum of sequence of natural numbers;
     * 1: 1
     * 3: 1+2
     * 6: 1+2+3
     * 10:1+2+3+4
     */
    public problem12()
    {
        boolean notFound = true;
        int i = 1;
        int triangleNum = 0;
        while(notFound)
        {
            triangleNum += i;
            System.out.println( triangleNum );
            if( getDivisors( triangleNum ).size() > 500 )
                notFound = false;
            i++;
        }
        System.out.println( triangleNum );
    }
    /**
     * Get divisors.
     *
     * @param double num
     * @return ArrayList<Integer> divisors
     */
    public static ArrayList<Integer> getDivisors( int num )
    {
        ArrayList<Integer> returnArray = new ArrayList<Integer>();
        returnArray.add( new Integer( 1 ) );
        for( int i = 2; i <= num/i; i++ )
        {
            if( num%i == 0)
            {
                returnArray.add( new Integer( i ));
                returnArray.add( new Integer( (int)(num/i)));
            }
        }
        returnArray.add( new Integer((int)num) );
        return returnArray;
    }
    /**
     * MAIN.
     * 
     * @param args String[]
     */
    public static void main( String[] args )
    {
        new problem12();
    }
}
