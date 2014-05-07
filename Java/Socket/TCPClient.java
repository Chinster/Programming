import java.io.*;
import java.net.*;
/**
 * TCPClient.java.
 *
 * @author Christopher Chin
 *
 */
public class TCPClient
{
    /**
     * Sends a line to a server, receives a modified line.
     * 
     * @param argv[] String
     */
    public static void main( String argv[] ) throws Exception
    {
        //Creates a reader of a stream of System.in (input from keyboard)
        BufferedReader inFromUser = new BufferedReader( new InputStreamReader(System.in) );
        //Opens a socket on port 8000 at hostname
        Socket clientSocket = new Socket("hostname", 8000);
        //Creates an output stream
        DataOutputStream outToServer = new DataOutputStream( clientSocket.getOutputStream() );
        //Creates a reader on the opened socket
        BufferedReader inFromServer = new BufferedReader( new InputStreamReader( clientSocket.getInputStream() ) );
        //Applies the input from user into the String variable
        String sentence = inFromUser.readLine();
        //Writes the sentence into the output stream
        outToServer.writeBytes(sentence + '\n' );
        //Applies the input from the server into the String variable
        String modifiedSentence = inFromServer.readLine();
        //Prints modified input
        System.out.println( "FROM SERVER: " + modifiedSentence );
        //closes socket.
        clientSocket.close();
        
    }
}
