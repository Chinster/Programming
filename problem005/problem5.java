/**
 * Project Euler - Problem 5 Solution.
 * problem5.java.
 *
 * @author Christopher Chin
 *
 */
public class problem5
{
    
    /**
     * Finds the smallest positive number divisible by the numbers 1-20.
     * 
     */
    public problem5()
    {
        //Must be a multiple of the products of the primes: 3, 5, 7, 11, 13, 17, 19
        //This product is 4849845.
        boolean divisible = false;
        long magicNumber = 4849845;
        while( !divisible )
        {
            if( magicNumber%20 == 0 ) //multiple of 4, 10, 20
                if( magicNumber%18 == 0 ) // multiple of 6, 9, 18
                    if( magicNumber%16 == 0 ) // multiple of 8, 16
                        if( magicNumber%14 == 0 ) //multiple of 14
                            divisible = true; // 4*3 -> multiple of 12
            System.out.println( magicNumber );
            magicNumber *= 2;      
        }
        System.out.println( magicNumber/2 );
    
    }
    
    /**
     * MAIN.
     * 
     * @param args String[]
     */
    public static void main( String[] args )
    {
        new problem5();
    }
}
