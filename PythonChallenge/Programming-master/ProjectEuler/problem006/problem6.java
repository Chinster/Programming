/**
 * Project Euler - Problem 6 Solution.
 * problem6.java.
 *
 * @author Christopher Chin
 *
 */
public class problem6
{
    
    /**
     * Finds the difference between the sum of the squares of 
     * the first one hundred natural numbers
     * and the square of the sum.
     * (1+2+3+4+5)^2 - 1+4+9+16+25 = ? 
     *
     */
    public problem6()
    {
        int sum = 0; //summation of numbers 1-100
        int sumOfSquared = 0; //summation of 1 squared, 2 squared, 3 squared...
        for( int i = 1; i <= 100; i++ )
        {
            sum += i;
            sumOfSquared += i * i; //Math.pow( i, 2 ); would convert to double, may lose accuracy.
        }
        int sumSquared = sum * sum; //MAX_INT = 2^31 - 1 = 2, 147, 483, 647
        System.out.println( sumSquared - sumOfSquared );
    }
    
    /**
     * MAIN.
     * 
     * @param args String[]
     */
    public static void main( String[] args )
    {
        new problem6();
    }
}
