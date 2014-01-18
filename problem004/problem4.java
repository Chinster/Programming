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
        int j = 999;
        int i = 999;
        while( i >= 100 )
        {
            if( isPalindrome( Integer.toString( i * j ) ) )
                break;
            j--;
            if( isPalindrome( Integer.toString( i * j ) ) )
                break;
            i--;
        }
        String largestPalindrome = Integer.toString( i * j );
        System.out.println( i + " * " + j + " = " + largestPalindrome );

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
