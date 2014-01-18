/**
 * Project Euler - Problem 9 Solution
 * problem9.java.
 *
 * @author Christopher Chin
 *
 */
public class problem9
{
/**
 * Find the product of the pythagorean triplet for which a + b + c = 1000.
 *
 */
public problem9()
{
    int[] squares = new int[500];
    int a = 0, b = 0, c = 0;
    for( int i = 0; i < 500; i++ )
        squares[i] = (int)Math.pow( i+1, 2 );
    for( int i = 2; i < 500; i++ )
    {
        for( int k = i-1; k > 1; k--)
        {
            for( int j = 0; j < k; j++ )
            {
                if( squares[i] - squares[k] == squares[j] )
                {
                    int C = (int)Math.sqrt(squares[i]);
                    int B = (int)Math.sqrt(squares[k]);
                    int A = (int)Math.sqrt(squares[j]);
                    //System.out.println("Pythagorean triple found: " + A + ", " + B + ", " + C );
                    //System.out.println("Sum = " + (A+B+C) );
                    if( (A + B + C) == 1000 )
                    {
                        a = A;
                        b = B;
                        c = C;
                    }
                }
            }
        }
    }
    System.out.println( a + ", " + b + ", " + c + " is a pythagorean triplet." );
    System.out.println( a + " + " + b + " + " + c + " = 1000" );
    System.out.println( a + " * " + b + " * " + c + " = " + a*b*c );
    }

    /**
     * Determines if three side lengths form a right triangle.
     *
     *
     */
    /**
     * MAIN.
     * 
     * @param args String[]
     */
    public static void main( String[] args )
    {
        new problem9();
    }
}
