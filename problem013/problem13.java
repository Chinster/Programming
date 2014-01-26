import java.util.ArrayList;
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
/**
 * problem13.java.
 *
 * @author Christopher Chin
 *
 */
public class problem13
{
    
    /**
     * Give the first 10 digits of the sum of the 50 digit numbers.
     *
     */
    public problem13()
    {
        ArrayList<String> numbers = new ArrayList<String>();
        try
        {
            File holyNumber = new File("./holy-number");
            Scanner scanFile = new Scanner( holyNumber );
            String theHolyNumber = scanFile.next();
            for( int i = 0; theHolyNumber.length() > 0; ) // break into 50 digits
            {
                numbers.add( theHolyNumber.substring( 0, 50 ) );
                if( theHolyNumber.length() > 50 )
                    theHolyNumber = theHolyNumber.substring( 50 );
                else
                    theHolyNumber = "";
            }
            for( String c: numbers )
            {
                System.out.println( "50-digit num: " + c );
            }
        }
        catch( FileNotFoundException e )
        {
            System.out.println( e.getMessage() );
        }
        catch( Exception e )
        {   
            System.out.println( e.getMessage() );
        }

    }
    
    /**
     * MAIN.
     * 
     * @param args String[]
     */
    public static void main( String[] args )
    {
        new problem13();
    }
}
