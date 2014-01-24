/**
* Project Euler - Problem 4 Solution.
* problem4.java.
*
* @author Christopher Chin
*
*/
public class problem4
{
/**
* Finds the largest palindrome that is the product of two three digit numbers.
*
*/
    public problem4()
    {
        int x = -1;
        int y = -1;
        int largestPalindrome = 1;
        for( int i = 999; i >= 100; i-- )
        {
            int limit = largestPalindrome / i;
            for( int j = i; j > limit; j--)
            {
                if( isPalindrome( Integer.toString( i * j ) ) )
                {
                    x = i;
                    y = j;
                    largestPalindrome = i * j;
                    break;
                }
            }
        }
        System.out.println( x + " * " + y + " = " + largestPalindrome );

    }
/**
 * Determines if an input is a palindrome.
 * 
 * @param testString String
 */
    public static boolean isPalindrome( String testString )
    {
        for( int i = 0; i < testString.length()/2; i++ )
        {
            if( testString.charAt(i) != testString.charAt( testString.length() - 1 - i ) )
            {
                return false;
            }
        }
        return true;
    
    }
/**
* MAIN.
*
* @param args String[]
*/
    public static void main( String[] args )
    {
        new problem4();
    }
}
